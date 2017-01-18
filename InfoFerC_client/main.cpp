#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare
  		// mesajul trimis
  int nr=0;
  char buf[10];

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);

  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }


  struct login
  {
    char username[255];
    char password[255];
  } loginDetails;
  //scanf("%d",&nr);


  strncpy(loginDetails.username,"admin", sizeof("admin"));
  strncpy(loginDetails.password,"root", sizeof("root"));


  struct response
    {
        char dep_station[255];
        char arr_station[255];
        int dep_time;
        int arr_time;
    } query ;

    strncpy(query.dep_station,"Iasi",sizeof("Iasi"));
    strncpy(query.arr_station,"Suceava",sizeof("Suceava"));
    query.dep_time=0;
    query.arr_time=85000;

  printf("Trimite login\n");

  /* trimiterea mesajului la server */
  if (write (sd,&loginDetails,sizeof(loginDetails)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

    printf("Trimite query\n");

     if (write (sd,&query,sizeof(query)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

  /* citirea raspunsului dat de server
     (apel blocant pina cind serverul raspunde) */

  /* afisam mesajul primit */
  printf ("[client]Mesajul primit este: %d\n", nr);

  /* inchidem conexiunea, am terminat */
  close (sd);
}
