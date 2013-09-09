#include <stdio.h>
#include <stdlib.h>

FILE * testFILE;

static void process(FILE *f)
{
    int c, estado;
    /* c de caracter, estado se usara para poder movernos dentro del switch,
    f es el archivo correspondiente y EOF es End Of File */
    estado = 0;

	while ((c=getc(testFILE)) != EOF)
    {
		switch(estado)
		{
			case 0: // Cuando se tiene un input inicial
				if(c == '"') // Cuando tenemos un string
                {
                    estado = 1;
                }

				else if(c == '\'') //Encontramos una literal
                {
                    estado = 2;
                }

				else if(c == '/') //Encontramos la primera diagonal para un comentario!
                {
					c = EOF;
					estado = 3;
				}
				break;

			case 1: // Cuando se esta adentro de un string
				if(c == '"')
                {
                    estado = 0;
                }
				break;

			case 2: // Adentro de una literal
				if(c == '\'')
                {
                    estado = 0;
                }
				break;

			case 3: // Ahora si a encontrar comentarios
				if(c == '/') // Se encontró la segunda diagonal de un comentario de linea
                {
					c = EOF;
					estado = 4;
				}

				else if(c == '*') // Se encontro un comentario en bloque
                {
					c = EOF;
					estado = 5;
				}

				else if(c == '\\') // Para salto de linea, en caso de que se quiera romper lineas (break lines)
                {
					c = EOF;
					estado = 7;
				}
				else //Falló en encontrar comentario simplemente pon la diagonal
				{
					putchar('/');
					estado = 0;
				}
				break;

			case 4: // Ya que se encontró las 2 diagonales de comentario
				if(c == '\\') //En caso de que se tenga algo para romper lineas (line break)
                {
					c = EOF;
					estado = 8;
				}

				else if(c == '\n') //Cuando se tiene un salto de línea
                {
					estado = 0;
                }

				else
                {
                    c = EOF;
                }

				break;

			case 5: // Adentro del comentario en bloque
				if(c == '*') //Se encontro un posible fin al comentario en bloque
                {
                    estado = 6;
                }

				c = EOF;
				break;

			case 6: // Adentro del fin del comentario en bloque
				if(c != '/') // Si es que aun no termina el comentario, que regrese al estado anterior
                {
					estado = 5;
					c = EOF;
				}

				else // Si es que es el fin del output/salida
                {
					estado = 0;
					c = ' ';
				}

				break;

			case 7: // Adentro del line break para comentarios en bloque
				if(c == '\n') //Cuando se tiene un salto de línea
                {
					estado = 3;
					c = EOF;
				}

				else
                {
					putchar('\\');
					estado = 0;
				}

				break;

			case 8: // Cuando se tiene un line break para comentarios de linea
				if(c == '\n') //Cuando se tiene un salto de línea
                {
                   c = EOF;
                }

				estado = 4;
				break;

		}

		if(c != EOF)
        {
            putchar(c);
        }

	}
}

int main(void)
{
    char fullname[256];
    sprintf(fullname, "C:\\Users\\Felipe Gonzalez\\Documents\\CETYS\\Test.txt"); //Cambiar el nombre del path?
    testFILE = fopen (fullname,"r+"); // el r+ para abrir un archivo para lectura y escritura

    if(testFILE) //Ver si el fichero tiene una direccion valida
    {
        printf( "Fichero abierto\n---\n" );
    }

   else
   {
        printf( "ERROR no se encontro fichero\n" );
        return 1;
   }

    process(testFILE);

    if( !fclose(testFILE) ) //Cerrar el fichero
    {
        printf("---\nFichero cerrado\n");
    }

   else
   {
      printf("--- \n Error: fichero NO cerrado\n");
      return 1;
   }

	return 0;
}
