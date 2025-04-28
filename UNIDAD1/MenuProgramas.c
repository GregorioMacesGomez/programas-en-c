#include <stdio.h>
int main () {
    printf("%s\n", "seleccione una opcion en letra");
    printf("%s\n", "a) Programa de escapes");
    printf("%s\n", "b) Programa para ver los tipos de datos");
    printf("%s\n", "c) Programa para obtener volumen de una esfera");
    printf("%s\n", "d) Programa para obtener temperatura con enteros");
    printf("%s\n", "e) Pograma imprime pesos y asteriscos");
    printf("%s\n", "f) Programa imprime una piramide de asteriscos");
    printf("%s\n", "g) Programa para obtener el promedio");
    printf("%s\n", "h) Programapara impirmir un trapecio asteriscos");
    printf("%s\n", "i) Programa para obtener temperatura con punto decial");
    printf("%s\n", "j) Programa imprime una diagonal de asteriscos");
    printf("%s\n", "k) Programa imprime cuadro de numeros");
    printf("%s\n", "l) Pograma imprime cuadro de asteriscos");
    printf("%s\n", "m) Programa para obtener volumen y area de un cono");
    printf("%s\n", "n) Programa para obtener volumen y area de un cilindro");
    printf("%s\n", "o) Programa para obtener volumen y area de un esfera");
    printf("%s\n", "p) Programa de un prueba switch 1");
    printf("%s\n", "q) Programa de una calculadora");
    printf("%s\n", "r) Programa de un 'hola mundo'");
    printf("%s\n", "s) Programa de una prueba switch 2");
    char opc;
    scanf("%c", &opc);
    switch (opc)
    {
    case 'a':
        printf("\\a Alarma\n");
        printf("\\b Retroceso\n");
        printf("\\f Avance de pagina\n");
        printf("\\n Retorno de carro y avance de linea\n");
        printf("\\r Retorno de carro\n");
        printf("\\t Tabulacion\n");
        printf("\\\\ Diagonal invertida\n");
        printf("\\? Signo de interrogacion\n");
        printf("\\\" Comillas dobles\n");
        printf("\\000 Octal\n");
        printf("\\xhh Hexadecimal\n");
        printf("\\0 Caracter nulo\n");
        return 0;
        break;
    case 'b':
        printf("%s","%d Imprime datos enteros decimales: 5\n");
        printf("%s","%i Imprime datos enteros: 2\n");
        printf("%s","%o Imprime datos octales: 6\n");
        printf("%s","%x Imprime datos hexadecimales: 8A1\n");
        printf("%s","%u Imprime datos enteros sin signo en decimal: 23\n");
        printf("%s","%c Imprime datos de caracteres: #\n");
        printf("%s","%e Imprime datos reales expresados en base y exponente:5^2 \n");
        printf("%s","%f Imprime datos reales escrito con punto decimal: 23.12\n");
        printf("%s","%g Imprime datos reales : 14\n");
        printf("%s","%s Imprime cadenas de caracteres: Hola123\n");
        printf("%s","%lf Imprime datos reales de tipo long double: 2.1646466565466642\n");
        return 0;
        break;
    case 'c':
        {
        int r = 5; //declaramos las variables
        float v; //volumen//
        float p = 3.1416; //le damos valor a pi

        v = (4 * p * r * r * r) / 3; //hacemos la operacion del radio

        printf("volumen%f\n",  v); //se imprime el resultado
        return 0;
        }
        break;
    case 'd':
        {
        int fahr, celsius, lower, upper, step; //declarar variables 
        lower = 0 ;
        upper = 300 ;
        step = 20 ;
        fahr = lower;
        while (fahr<= upper) { //ciclo aqui enoieza con la condicional
            celsius = 5 * (fahr-32) / 9; //aqui hace la operaciones 
            printf("%d\t%d \n", fahr, celsius); // imprime todo hasta que ya no se acomplete el ciclo
            fahr=fahr+step; //incremento 
        }
        }
        break;
    case 'e':
        {
        int espacio=6;
        int asterisco=1;
        for(int i=6; i>=0; i--){
            for(int j=1; j<=espacio; j++){
                printf("%4s", "$");
            }
        espacio--;
        for (int k=1; k<=asterisco; k++){
            printf("%4s","*");
        }
        asterisco++;
        printf("\n");
        }
        }
        break;
    case 'f':
        {
        int espacios=6;
        int asterisco=1;
        for (int i=6; i>=0; i--){
            for(int j=1; j<=espacios; j++){
                printf("%4s","/");
            }
            espacios --;
            for (int k=1; k<=asterisco; k++){
                printf("%4s","*");
            }
            asterisco +=2;
            printf("\n");
        }
        }
        break;
    case 'g':
        {
        char nombre[50];
        printf("%s\n", "ingrese su nombre");
        scanf("%s", &nombre);
        int cal1;
        printf("%s\n", "dame calificacion 1");
        scanf("%d", &cal1);
        int cal2;
        printf("%s\n", "dame calificacion 2");
        scanf("%d", &cal2);
        int cal3;
        printf("%s\n", "dame calificacion 3");
        scanf("%d", &cal3);
        float prom;
        prom = (cal1 + cal2 + cal3) / 3;
        printf("%s%s\n", nombre);
        printf("%s%.2f\n", "tu promedio es:", prom);
        if (prom >= 6)
        {
            printf("%s\n", "aprobado");
        }
        else
        {
            printf("%s\n", "reporbado");
        }
        }
        break;
    case 'h':
        {
        int espacio=4;
        int asterisco=3;
        for( int i=3; i>=0; i--){
            for(int j=1; j<=espacio;j++){
                printf("%4s", "");
            }
            espacio --;
            for (int k=1; k<=asterisco;k++){
                printf("%4s","*");
            }
            asterisco +=2;
            printf("\n");
        }
        }
        break;
    case 'i':
        {
        int lower, upper, step;
        float fahr, celsius; //declarar variables 
        lower = 0 ;
        upper = 300 ;
        step = 20 ;
        fahr = lower;
        while (fahr<= upper) { //ciclo aqui enoieza con la condicional
            celsius = (5.0/9.0) * (fahr-32.0); //aqui hace la operaciones 
            printf("%3.0f%6.1f \n", fahr, celsius); // imprime todo hasta que ya no se acomplete el ciclo
            fahr=fahr+step; //incremento 
        }
        }
        break;
    case 'j':
        {

        int espacio=1;
            
        for(int a=9;a>=0;a--){

        for(int b=2;b<=espacio;b++){
            printf("%4s"," ");
        }
        
        espacio++;
        printf("%4s","*");
        printf("\n");

        }
        return 0;
        }
        break;
    case 'k':
        { 

        int contador = 0;
        int limite = 10;
         
        printf("%4s\n", "Ejemplo de impresion");
        while (contador <= limite) {
    
                printf("%4d", contador);
                contador++;
        }
        printf("\n%s\n", "ejemplo de impresiom");
    
        int limitey = 10;
        while (limitey >= 0) {
            int limitex = 10;
            while (limitex >= 0) {
                printf("%4d", limitex);
                limitex--;
    
            }
            printf("\n");
            limitey--;
        }
    
        printf("\n%s\n","ejemplo de impresion");
    
        int limitesy = 0;
        while (limitey <= 10) {
            int limitex = 0;
            while (limitex <= 10) {
                printf("%4d", limitex);
                limitex++;
    
            }
            printf("\n");
            limitey++;
        }
    
        printf("\n%s\n","ejemplo de impresion");
        return 0;
        }
        break;
    case 'l':
        {

        for (int a=0;a<=9;a++){
            printf("%3s","*");
        }
        printf("\n");
        for(int b=1;b<=7;b++){
            printf("%3s","*");
    
            for (int c=1;c<=8;c++){
                printf("%3s"," ");
            }
    
            printf("%3s","*");
            printf("\n");
    
        }
        for (int a=0;a<=9;a++){
            printf("%3s","*");
        }
        return 0;
        }
        break;
    case 'm':
        {
        float radio;
        float altura;
        float volumen;
        float pi=3.1416;
        //float alateral;
        float atotal;
        float hipotenusa;
        printf("dame el valor de la altura\n");
        scanf("%f",&altura);
        printf("%s\n","dame el valor del radio");
        scanf("%f",&radio);
        hipotenusa=(radio*radio)+(altura*altura);
        //alateral=(pi*radio*hipotenusa);
        atotal=(pi*radio*radio)+(pi*radio*hipotenusa);
        volumen=(pi*radio*radio*altura)/3;
        printf("el volumen es: \n %f\n", volumen);
        printf("el area total es: \n %.2f \n",atotal);
        }
        break;
    case 'n':
        {
        float h;
        float radio;
        float pi=3.1416;
        float volumen;
        float area;
        printf("%s\n", "dame el valor de la altura de tu cilindro");
        scanf("%f", &h);
        printf("%s\n", "dame el radio de la circunferencia de tu cilindro");
        scanf("%f", &radio);
        volumen =(pi*radio*radio*h);
        area = ((2*pi)*(radio*h)+(2*pi*radio*radio));
        printf("%s%.4f\n", "el volumen es \n", volumen);
        printf("%s%.2f\n", "el area es: \n", area);
        }
        break;
    case 'o':
        {
        float radio;
        float volumen;
        float pi=3.1416;
        float area;
        printf("%s\n", "dame el valor del radio");
        scanf("%f", &radio);
        volumen= (4*pi*radio*radio*radio)/3;
        area=(4*pi*radio*radio);
        printf("%s%.4f\n", "el volumen es \n", volumen);
        printf("%s%.2f\n", "el area es: \n", area);
        }
        break;
    case 'p':
        {
        int opc;
        printf("%s\n","seleccione una opcion");
        printf("%s\n","1-sumar");
        printf("%s\n","2-restar");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            printf("%s\n", "ha seleccionado suma");
            break;
        
        case 2:
            printf("%s\n", "ha seleccionado resta");
            break;
        
        default:
            printf("%s\n","no ha seleccionado una opcion valida");
            break;
        }
        return 0;
        }
        break;
    case 'q':
        {
        int opc;
        int num1;
        int num2;
        int suma, resta, multi, div;
        printf("%s\n","seleccione una opcion");
        printf("%s\n","1-sumar");
        printf("%s\n","2-restar");
        printf("%s\n","3-multiplicacion");
        printf("%s\n","4-division");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            printf("%s\n", "dame el primer numero");
            scanf("%d", &num1);
            printf("%s\n", "dame el segundo numero");
            scanf("%d", &num2);  
            suma=(num1+num2);
            printf("%s%d\n", "el resultado es:\t", suma);
            break;
        case 2:
            printf("%s\n", "dame el primer numero");
            scanf("%d", &num1);
            printf("%s\n", "dame el segundo numero");
            scanf("%d", &num2);  
            resta=(num1-num2);
            printf("%s%d\n", "el resultado es:\t", resta);
            break; 
        case 3:
            printf("%s\n", "dame el primer numero");
            scanf("%d", &num1);
            printf("%s\n", "dame el segundo numero");
            scanf("%d", &num2);  
            multi=(num1*num2);
            printf("%s%d\n", "el resultado es:\t", multi);
            break;
        case 4:
            printf("%s\n", "dame el primer numero");
            scanf("%d", &num1);
            printf("%s\n", "dame el segundo numero");
            scanf("%d", &num2);  
            div=(num1/num2);
            printf("%s%d\n", "el resultado es:\t", div);
            break;
        default:
            printf("%s\n","no ha seleccionado una opcion valida");
            break;
        }
        return 0;
        }
    case 'r':
        {
        printf("hola mundo");
        } 
        break;
    case 's':
        {
        printf("%s\n", "seleccione una opcion");
        printf("%s\n", "a) Seleccionar opcion 1");
        printf("%s\n", "b) seleccionar opcion 2");
        char opc;
        scanf("%c", &opc);
        switch (opc)
        {
        case 'a':
            printf ("%s\n", "seleccione opc1");
            break;
        case 'b':
            printf("%s\n", "selecciona opc 2");
            break;
        default:
            printf("%s\n", "Opcion invalida");
            break;
        }
        return 0;
        break;
        }
    default:
        printf("%s\n","no ha seleccionado una opcion valida");
        break;
    }
}