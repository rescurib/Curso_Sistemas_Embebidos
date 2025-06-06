# Guía de estudio para sistemas embebidos

## Introducción

Gracias a internet, y a una enorme comunidad de creadores de contenido, vivimos en una época dorada para el auto-aprendizaje. El único problema es que existen muchos temas para los cuales la abundancia de información llega a ser abrumadora. Necesitamos de guías que nos ayuden a navegar en este extenso mar. Los sistemas embebidos es un ejemplo claro de esta situación, no sólo para la diversidad de sus implementaciones sino tambien la de sus aplicaciones:  

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/SistemasEmbebidosAplicaciones.png" width="680">
<p>

Nota: Otra area de aplicación que ha cobrado mucha importancia para la transición a energías limpias es la de [potencia digital aplicada a sistemas de energía eléctrica](https://www.st.com/content/st_com/en/ecosystems/stm32-digital-power.html) (una buena apuesta para demanda laboral futura).

¿Pero qué es un sistema embebido en primer lugar? Una definición concisa aparece en el glosario del sitio del fabricante de dispositivos electrónicos [Analog Devices](https://www.analog.com/en/design-center/glossary/embedded-system.html):

>Un sistema embebido es un sistema en el que la computadora (generalmente un microcontrolador o microprocesador) se considera como parte integral del sistema.

Me parece una definición simple y adecuada porque facilita el pensar en sitemas que NO son embebidos: super-computadoras utilizadas en simulaciones de procesos fisicos/biologicos, servidores que proveen servicios de nube o computadoras personales. ¿En qué casos si se considera a una computadora como parte integral de sistema? Algunos ejemplos son:

* Smart phones
* Smart watches
* Satélites
* Robótica móvil
* Controladores de procesos industriales

Personalmente me desagrada la traducción de *embedded* como *incrustado* pero admito que esa palabra da la buena intuación de una computadora que **incrusta** en un producto de consumo o sistema más grande (autos, aviones o lineas de ensamblaje).

### A quíen va dirigida esta guía

Estudiantes/egresados de ingenierías, ciencias físicas o profesionistas con planes de pivotear como desarolladores de sistemas embebidos. Las guías de estudio y el curso de STM32 de este repo tienen la intención de mostrar los temas esenciales para ejercer como un desarollador profesional. Estos temas estarán sobrados para quienes tengan la intención de ser hobbistas (soy fan del ecosistema Arduino y considero que es una excelente plataforma para ese propósito). Hago esta última aclaración no por soberbia sino con la intención de enfatizar el tiempo y esfuerzo requerido para completar todo el road-map. El desarrollo y entendimiento de los sistemas embebidos es una habilidad académica que tiene un retorno rápido de inversión. Recomiendo buscar las [vacantes que ofertan en Linkedin](https://www.linkedin.com/jobs/search/?currentJobId=3497879218&keywords=Embedded%20System%20Engineer&refresh=true) y ver los requisitos de cada una para ajustar los temas en los que necesitan poner atención adicional. 

## Guía bibliográfica general para dominar el auto-apendizaje
Mi sagrada trinidad de libros en el tema que siempre recomiendo. Afortunadamente todos[^1] pueden encontrarse en ediciones en español:
* [Make it Stick (Apréndetelo), Peter Brown, Mark McDaniel, Henry Roediger](https://www.amazon.com.mx/Make-Stick-Science-Successful-Learning/dp/0674729013). El mejor libro que conozco con ténicas de estudio efectivas respaldadas por estudios.
* [Ultralearning, Scott Young](https://www.amazon.com.mx/Ultralearning-Aprende-R%C3%A1pido-Alcanza-Objetivos/dp/8416883742/). El autor logró estudiar por su cuenta todo el plan de estudios de la carrera de Ciencias Computacionales del MIT pasando todos los exámenes en tiempo record. Este libro detalla las técnicas de autoestudio que descubrió durante el proceso. 
* [Deep Work (Enfócate), Cal Newport](https://www.amazon.com.mx/Enf%C3%B3cate-Cal-Newport/dp/6077473421). El autor es un computólogo profesor-investigador que ha popularizado las ventajas de trabajar sin distracciones por tiempos cortos (45 a 90 minutos) y largos, y las reglas que hay que seguir para lograrlo.

[^1]: Make it Stick (Apréndetelo) dejó de ser editado en español por Paidos pero puedes encontrarlo en formato .epub *si sabes dónde buscar*. Puedes abrir esos archivos en tu móvil con la app Lithium. 

## Guía bibliografica fundamental para sistemas embebidos
Quiero comenzar desmintiendo un consejo que he visto muy a menudo en foros en el que se dice que para conseguir un trabajo como desarollador debes ser experto en todas las areas que cubren los sistemas embebidos: lenguajes de descripción de hardware, visión por computadora, Linux embebido, procesamiento digital de señales, teoría de control, radio comunicaciones, diseño de circuitos impresos, diseño de fuentes de alimentación y un largo etc... Esto no es verdad. Ciertamente existen muchos desarolladores veteranos (10-30 años de experiencia) que pueden dominar muchas areas, pero en la práctica es suficiente con que elijas unas pocas especializaciones para conseguir una buena posición. La guía que propongo es la base para conseguir una empleo como desarrollador Jr y es también la base de conocimiento sobre la cual especializarte más adelante según tu preferencia o retos laborales que se te vayan presentando.

### 1: Electrónica Básica
En mi blog publiqué una guía bibliográfica completa para cubrir el *core* escencial para una ingeniería en electrónica. Puedes consultarla [acá](http://stg-pepper.blogspot.com/2018/06/guia-bibliografica-para-aprender.html) si lo deseas pero estará muy sobrada. Lo que hice fue reducirla de manera que cubra lo mínimo que necesitamos acá:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Electronica_Minimo.png" width="700">
<p>

Por supuesto, si ya estudias o vienes de una ing. en mecatrónica o electrónica puedes omitir esta parte. 

Si quieren profundizar en los cálculos (opcional), [LTSpice](https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html) es una herramienta muy buena para hacer simulaciones. [Aquí](https://www.youtube.com/playlist?list=PLPYWiDnEtp4N6emDF98TFxZyw-EDc3pcw) hay un curso en español. 
  
Recomiendo también instalar [Kicad](https://www.kicad.org/), que es una plataforma de diseño de circuitos impresos gratuita y de código abierto. [Aquí](https://www.youtube.com/playlist?list=PLkyFkq6L7y6tmqIB3yqkS0UnTWYbsH3wn) hay un curso en Youtube muy bueno hecho por [Antonio Raptors](https://github.com/antonioraptors).

### 2: Lenguaje C y Arquitectura de Computadoras
Ahora comenzamos con el corazón de los sistemas embebidos basados en procesadores. Como desarollador de firmware puedo asegurar que el entender la arquitectura de los procesadores no es mera *cultura general* sino una necesidad real a la hora de resolver problemas y diseñar software embebido. Es verdaderamente importante llevar el estudio de la arquitectura de la mano del estudio profundo del lenguaje C:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Lenguaje_C_Arquitectura_Computadoras.png" width="710">
<p>
  
  #### Visual Studio Code
  Si compilar desde terminal con gcc llega a ser muy tedioso, puedes instalar [Visual Studio Code](https://code.visualstudio.com/) y seguir [este tutorial](https://www.youtube.com/watch?v=iPvvbNVisfU) para configurar la extensión para C/C++.
  
  #### Estándares de código
  
En las entrevistas que me han tocado (como entrevistado y entrevistador) el tema de los estandares de código es opcional para vacantes de entre 0 y 2 años de experiencia. No está de más que sepas que es [MISRA C](https://la.mathworks.com/discovery/misra-c.html). No hace falta que memorices las cientos de reglas que tiene el estandar (en la práctica se revisa con [analizadores estáticos](https://es.wikipedia.org/wiki/An%C3%A1lisis_est%C3%A1tico_de_software)) pero si es ventajoso que puedas responder qué es y para qué se usa. 
  
  El estandar que si recomendaría aprender y usar es el [Barr Embedded C Coding Standard](https://barrgroup.com/embedded-systems/books/embedded-c-coding-standard). Es bastante corto, práctico y le dará puntos a tus repos de Github.
  
  #### Computer Architecture Lectures (opcional)
  Si no tienes problemas con el inglés escuchado, mi clase favorita es la del profesor Onur Mutlu. Puedes ver todo el curso en Youtube en [esta](https://www.youtube.com/playlist?list=PL5PHm2jkkXmi5CxxI7b3JCL1TWybTDtKq) lista de reproducción.
  
  #### Algoritmos y Estructuras de Datos
  Estrictamente necesario ver [este](https://youtu.be/-j4hFcifLWc) excelente video sobre el manejo de memoria en C de [José Colbes](https://www.youtube.com/@ochecolbes/videos) para entender que son el heap y el stack. Después continuar con:
  
  *Estructuras de Datos en C*, Luis Joyanes
  * Cap. 5: Algoritmos de búsqueda y ordenación
  * Cap. 7: Tipos abstractos de datos y objetos
  * Cap. 8: Listas, listas enlazadas
  * Cap. 9: Modificaciones de listas enlazadas
  * Cap. 10: Pilas y sus aplicaciones
  * Cap. 11: Colas, colas de prioridad y montículos
 
  Si este libro les parece muy formal pueden intentar con *Programacion En C/C++ Java Y Uml* también de Luis Joyanes (tiene capítulos que cubren esos temas). Es más accesible y más facil de conseguir en librerias. 
  
### 3: Microcontroladores 
Teniendo estudiadas las guías 1 y 2 ya tienes todo lo necesario para aprovechar al máximo [mi curso de STM32](https://github.com/rescurib/Curso_Sistemas_Embebidos/tree/main/CursoSTM32). La siguiente guía puede estudiarse simultánemente. En el curso cubriré más temas como máquinas de estado, schedulers y parsers pero estaré haciendo referencias a estos dos libros así que recomiendo seguirla completamente:
<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Guia_Microcontroladores.png" width="710">
<p>
  
  Si ya has desarrollado otros tipos de software seguramente sabes usar Git. Si no es así (Git y Github no son lo mismo), es importante que te familiarices con esta herramienta. [Aquí](https://www.youtube.com/playlist?list=PLdX95r_5VhojrYffoY3OEySCW4RlEtaMG) hay un curso en español de Git desde terminal y con Sourcetree. Puedes practicar creando repos de tus prácticas de microcontroladores y subir o corregir tus cambios con Sourcetree. Uno de los mejores libros sobre Git es [*Pro Git* de Scott Chacon](https://git-scm.com/book/en/v2) ¡y es gratis!
  
  Si han estudiado hasta este punto, tienen bien asimilado todo y además tienen inglés conversacional B2 fluido, es suficiente para calificar muy bien en una entrevista para una posición de desarrollador de firmware Jr en varias empresas grandes de tecnología. Las siguientes secciones podrían no ser necesarias para entrar pero definitivamente si serán necesarias para su día a día como profesional.   
  
### 4: Ingeniería de Firmware
  En las aplicaciones reales no basta con que el código "parezca funcionar". El código debe escribirse de manera que facilite el ciclo de vida de un producto y el trabajo con tu equipo de desarrollo. Pensemos en las siguientes preguntas:
 * ¿Podemos añadir código de nuevas funcionalidades sin modificar demasiado el que ya existe?
 * ¿Puedo cambiar el microcontrolador sin que impacte tanto al proyecto entero?
 * ¿Puedo reutilizar el código de los módulos que ya tengo escritos para crear nuevos?
 * ¿Cómo implementar los requerimientos que debe cumplir el producto de forma adecuada?
 * Si sacamos al mercado productos distintos, ¿puedo agilizar la creación de nuevos proyectos firmware?

  Esta es la parte de ingeniería de firmware. La sintaxis del lenguaje y el funcionamiento de los periféricos son sólo los cimientos de los proyectos. El siguiente paso es aprender a implementar patrones de diseño. El sitio de Embbedded Artistry tiene una muy buena [recopilación de patrones de diseño](https://embeddedartistry.com/fieldatlas/design-pattern-catalogue/) para sistemas embebidos pero es fácil perderse si es la primera vez que se trabaja con ellos. En esta sección muestro un camino mejor navegable...  
  
  [En construcción]
  
 ### 5: Tiempo Real y Programación Orientada a Eventos

  [En construcción]
