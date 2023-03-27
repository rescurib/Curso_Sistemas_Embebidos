# Guía de estudio para sistemas embebidos

## Introducción

Gracias a internet, y a una enorme comunidad de creadores de contenido, vivimos en una época dorada para el auto-aprendizaje. El problema es que existen muchos temas para los cuales la abundancia de información llega a ser abrumadora. Necesitamos de guías que nos ayuden a navegar en este extenso mar. Los sistemas embebidos es un ejemplo perfecto de esta situación no solo para la diveridad de sus implementaciones sino tambien la de sus aplicaciones:  

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/SistemasEmbebidosAplicaciones.png" width="680">
<p>

Otra area de aplicación que ha cobrado mucha importancia para la transición a energías limpias es la de [potencia digital aplicada a sistemas de energía eléctrica](https://www.st.com/content/st_com/en/ecosystems/stm32-digital-power.html).

¿Pero qué es un sistema embebido en primer lugar? Una definición concisa aparece en el glosario del sitio del fabricante de dispositivos electrónicos [Analog Devices](https://www.analog.com/en/design-center/glossary/embedded-system.html):

>Un sistema embebido es un sistema en el que la computadora (generalmente un microcontrolador o microprocesador) se considera como parte integral del sistema.

Me parece una definición adecuada porque facilita el pensar en sitemas que NO son embebidos: super-computadoras utilizadas en simulaciones de procesos fisicos/biologicos, servidores que proveen servicos de nube o computadoras personales. ¿En qué casos si se considera a una computadora como parte integral de sistema? Algunos ejemplos son:

* Smart phones
* Smart watches
* Satélites
* Robótica móvil
* Controladores de procesos industriales

Personalmente me desagrada la traducción de *embedded* como *incrustado* pero admito que esa palabra da la buena intuación de una computadora que **incrusta** en un producto de consumo o sistema más grande (autos, aviones o lineas de ensamblaje).

### A quíen va dirigida esta guía

Estudiantes/egresados de ingenierías, ciencias físicas o profesionistas con planes de pivotear como desarolladores de sistemas embebidos. Las guías de estudio y el curso de STM32 de este repo tienen la intención de mostrar los temas esenciales para ejercer como un desarollador profesional. Estos temas estarán sobrados para quienes tengan la intención de ser hobbistas (soy fan del ecosistema Arduino y considero que es una excelente plataforma para ese propósito). Hago esta última aclaración no por soberbia sino con la intención de enfatizar el tiempo y esfuerzo requerido para completar todo el road-map. El desarrollo y entendimiento de los sistemas embebidos es una habilidad académicas que tiene un retorno rápido de dinero. Recomiendo buscar las [vacantes que ofertan en Linkedin](https://www.linkedin.com/jobs/search/?currentJobId=3497879218&keywords=Embedded%20System%20Engineer&refresh=true) y ver los requisitos de cada una para ajustar los temas en los que necitan poner más atención. 

## Guía bibliográfica general para dominar el auto-apendizaje
Mi sagrada trinidad del libros en el tema que siempre recomiendo. Afortunadamente todos[^1] pueden encontrarse en ediciones en español:
* [Make it Stick (Apréntelo), Peter Brown, Mark McDaniel, Henry Roediger](https://www.amazon.com.mx/Make-Stick-Science-Successful-Learning/dp/0674729013). El mejor libro que conozco con ténicas de estudio efectivas verdaderamente respaldas por estudios.
* [Ultralearning, Scott Young](https://www.amazon.com.mx/Ultralearning-Aprende-R%C3%A1pido-Alcanza-Objetivos/dp/8416883742/). El autor logro estudiar por su cuenta todo el plan de estudio de la carrera de Ciencias Computacionales del MIT pasando todos los exámenes en tiempo record. Este libro detalla las tenicas de autoestudio que descubrió durante el proceso. 
* [Deep Work (Enfócate), Cal Newport](https://www.amazon.com.mx/Enf%C3%B3cate-Cal-Newport/dp/6077473421). El autor es un computólogo profesor-investigador que ha popularizado las ventajas de trabajar sin distracciones por tiempos cortos (45 a 90 minutos) y las reglas que hay que seguir para lograrlo.

[^1]: Make it Stick (Apréntelo) dejó de ser editado en español por Paidos pero puedes encontrarlo en formato .epub *si sabes dónde buscar*. Puedes abrir esos archivos en tu móvil con la app Lithium. 

## Guía bibliografica fundamental para sistemas embebidos
Quiero comenzar desmintiendo un consejo que he visto muy amenudo en foros en el que se dice que para conseguir un trabajo como desarollador debes ser experto en todas las areas que cubren los sistemas embebidos: lenguajes de descripción de hardware, visión por computadora, Linux emebido y Yocto Project, procesamiento digital de señales, teoría de control, radio comunicaciones, diseño de circuitos impresos, diseño de fuentes de alimentación, etc... Esto no es verdad. Ciertamente existen muchos desarolladores veteranos (10-30 años de experiencia) que dominan casi todas esas areas pero en la práctica es suficiente con que elijas unas pocas especializaciones para conseguir una buena posición. La guía que propongo a continuación es la base para conseguir una posición Jr y es la base también sobre la cual especializarte más adelante segun tu prefeencia o retos laborales que lleguen a presentarte.

### 1: Electrónica Básica
En mi blog publiqué una guía bibliográfica completa para cubrir el *core* escencial para una ingeniería en electrónica. Puedes consultarla [acá](http://stg-pepper.blogspot.com/2018/06/guia-bibliografica-para-aprender.html) si lo deseas pero estará muy sobrada. Lo que hice fue reducirla de manera que cubra lo mínimo que necesitamos acá:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Electronica_Minimo.png" width="700">
<p>

Por supuesto, si ya estudias o vienes de una ing. en mecatrónica o electrónica puedes omitir esta parte.
### 2: Lenguaje C y Arquitectura de Computadoras
Aquí comienza el corazón de los sistemas embebidos. Cuando termines este camino podrás responder entre un 60% y 70% de las preguntas de una entrevista para una vacante Jr.

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Lenguaje_C_Arquitectura_de_Computadoras.png" width="710">
<p>

### 3: Microcontroladores 
<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Guia_Microcontroladores.png" width="710">
<p>

