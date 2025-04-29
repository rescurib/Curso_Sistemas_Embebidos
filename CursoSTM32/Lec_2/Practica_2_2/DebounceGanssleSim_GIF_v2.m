% Animación del anti-rebote tipo stem con valor binario de g_SW1_state

% Señal del botón (1 = no presionado, 0 = presionado) con rebotes iniciales
input_signal     = [0 0 0 0 0 1 1 0 0 1 1 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1];
n = length(input_signal);

% Inicializa variables
State = uint16(0);
state_bin_history = cell(1, n);  % <- Usa celdas en vez de strings

% Crea figura
f = figure;
hStem = stem(0, input_signal(1), 'filled');
axis([0 n -0.1 1.25]);
pbaspect ([1.6 1 1]);
set(gca, 'LooseInset', get(gca, 'TightInset'));
xlabel('Lecturas digitales (cada 2 ms)');
ylabel('HAL\_GPIO\_ReadPin(PORT,PIN)');
title('Animación Anti-Rebote');

% Texto para mostrar el valor binario de State
hText = text(n/2, 1.165, '', 'HorizontalAlignment', 'center', ...
             'FontName', 'Courier', 'FontSize', 16, 'FontWeight', 'bold');

% Texto adicional para mostrar el retorno de debounce
hReturn = text(n/2, 1.09, '', 'HorizontalAlignment', 'center', ...
                'FontName', 'Courier', 'FontSize', 14, 'FontWeight', 'bold');

delay_animacion = 0.75;
filename = "debounce_anim.gif";
gen_gif = false;

for i = 1:n
    raw = input_signal(i);

    % Lógica de debounce
    State = bitshift(State, 1);
    State = bitor(State, bitand(~raw, 1));  % !RawKeyPressed()
    State = bitor(State, hex2dec('E000'));

    % Guarda estado binario como string de caracteres
    state_bin = dec2bin(State, 16);
    state_bin_history{i} = state_bin;

    % Calcula retorno de sw_1_debounce
    if State == hex2dec('F000')
        ret_debounce = true;
    else
        ret_debounce = false;
    end

    % Actualiza gráfico
    set(hStem, 'XData', 0:i-1, 'YData', input_signal(1:i));
    set(hText, 'String', ['g\_SW1\_state: ' state_bin]);

    % Actualiza texto de retorno
    if ret_debounce
        set(hReturn, 'String', 'sw\_1\_debounce(): TRUE', 'Color', 'r');  % Rojo llamativo
    else
        set(hReturn, 'String', 'sw\_1\_debounce(): false', 'Color', 'k'); % Negro normal
    end

    drawnow;
    pause(delay_animacion);

    if gen_gif
      frame = getframe(f);
      im = frame2im(frame);
      [imind,cm] = rgb2ind(im);
      if i == 1
          imwrite(imind,cm,filename,'gif','DelayTime', delay_animacion , 'Compression', 'lzw');
      else
          imwrite(imind,cm,filename,'gif','WriteMode','append','DelayTime', delay_animacion , 'Compression', 'lzw');
      end
    end
end

