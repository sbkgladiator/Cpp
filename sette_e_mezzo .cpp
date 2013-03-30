/*
                -----            sette_e_mezzo.cpp              -----
	                           Prova pratica di
			           Giorgio Cerrito

--------------------------------------------------------------------------------------*/
//Il programma prevede di giocare una partita a 'sette e mezzo' tra due giocatori:
//giocatore e banco. All'inizio di ogni partita si puo' scegliere se il banco sara' un
//altra persona (assumendo quindi i comandi  da tastiera) o se sara' il computer a
//sfidare il giocatore tramite una strategia basata su diversi parametri.
//Il numero dei giocatori che sfidano il banco può inoltre arrivare fino a 20 ed è 
//permesso associare loro un nome ed ognuno di loro ha a disposizione 300 crediti
//per fare delle puntate come nella realtà.
//--------------------------------------------------------------------------------------

#include <iostream.h>  //  per cin>>  e  cout<<  
#include <stdlib.h>  //  per system() e rand()
#include <time.h>  //  per time()
#include <conio.h>  //  per getch()
#include <string.h>  //  per strlen()


//                           **----struct 'carta'------**
struct carta
//Come nella realtà ad ogni 'carta' viene attribuito un seme ed un valore numerico.
{
	int seme,numero;
};


//                           **----struct 'giocatore'----**
struct giocatore //Ad ogni 'giocatore' si associa un valore di punti e di 
                 //soldi e un nome(10 caratteri massimo).
{
	char nome[10];
	int punti,soldi;
};


//                             **---classe 'mazzo'---**
class mazzo //La classe mazzo serve per le operazioni da effettuare sul mazzo
//(creazione e mescolatura del mazzo, estrazione della carta) e tiene il conto delle  
//carte uscite durante la partita ('carte[10]').
//Ogni variabile di tipo astratto 'mazzo' rappresenta così un mazzo vero e proprio.
{
private:
	carta mazzoVet[40];//array delle carte del mazzo 
public:
	int carte[10];//tiene il conto delle carte estartte dal mazzo
	              //per la strategia del computer
	int matta; //utile al controllo per la matta
    void mescola(); //crea e mescola il mazzo(l'array) di carte
	carta dai_carta(); //estrae la carta e la rimuove dal mazzo
};


carta mazzo::dai_carta()
{ 
   carta estratta;//la carta estratta.	            
   estratta=mazzoVet[0];//estrae la prima carta del mazzo.
   if(estratta.numero==10 && estratta.seme==1)matta=1;//"int matta=1" ---> mescolatura a fine   
	                                             //partita;
   //La Matta è la decima carta del primo seme
         //---rimozione carta dal mazzo---
	for(int ri=0;ri<39;ri++)    //sposta le carte di una posizione 		
	mazzoVet[ri]=mazzoVet[ri+1];//
	                            //e viene assegnato zero all'ultima posizione		
	mazzoVet[39].numero=0;       //cosi'da rendersi conto
    mazzoVet[39].seme=0;     //quando sono finite le carte e bisogna   
		                         // quindi rimescolare il mazzo.
 carte[estratta.numero-1]++;//Incremento del parametro per la strategia del computer
   if(mazzoVet[0].numero==0)//Dopo aver eliminato la carta estratta controlla tra 
		         //quelle rimaste il valore della prima: se è uguale a zero significa
   {         //che il mazzo è finito e richiama la funzione mescola.
		   cout<<"\aMazzo finito!\n";// '\a' produce un suono
		   mescola();//parte quindi la mescolata del mazzo
   }
   return estratta;
}

void mazzo::mescola()
{
	
	int carts;//posizione della carta all'interno dell'array 'mazzoVet' che sarà 
	          //incrementato dopo ogni inserimento di carta nel mazzo.
	carts=0;//psizione della prima carta
	srand((unsigned)time(NULL)); //inizializzazione funzione rand().
     //---creazione mazzo ordinato di 40 carte
for(int ins=1;ins<11;ins++)     //numeri da 1 a 10  
 for(int ins2=1;ins2<5;ins2++)    //semi da 1 a 4
 {
	carta kar;
	kar.numero=ins;
	kar.seme=ins2;
    mazzoVet[carts]=kar; 
    carts++;          //
 }
//  ---mescolamento del mazzo ordinato---
		carta s;          
		for(int ctr=0;ctr<5;ctr++)//ciclo che per 5 volte mescola il
for(int mes=0;mes<20;mes++)   //mazzo scambiando le prime 20 carte con 
{                             //altre prese a caso nel mazzo
	int ra;
ra=rand()%40;//prende una carta a caso nell'array del mazzo.
if(mazzoVet[ra].numero!=mazzoVet[mes].numero && mazzoVet[ra].seme!=mazzoVet[mes].seme) 
                                      //controllo che la carta con cui effettuare
                                      //lo scambio non sia uguale a quella da scambiare.
{	
		    s=mazzoVet[mes];       
mazzoVet[mes]=mazzoVet[ra];
 mazzoVet[ra]=s;
}
}
for(int ini=0;ini<10;ini++)//inizializzazione del valore dell'array per il controllo 
carte[ini]=0;              //delle carte estratte dal mazzo.
cout<<"---->Mescolatura del mazzo effettuata.\n";
}

//                           **---classe 'setemez'---**
class setemez//Nella classe 'setemez' ci sono tutte le primitive che servono al
//gioco del sette e mezzo.
{
       // ----parte privata----
private:
	//le costanti inizializzate nella parte privata sono visibili ed
	//accessibili da tutte le funzioni della classe 'setemez'.
	mazzo maz; //il nostro mazzo di carte.
	carta ccg,ccb; //carte coperte del giocatore e del banco
	giocatore table[20]; //massimo 20 giocatori
    char gio2; //secondo giocatore(persona oppure CPU)
	int num_gioc; //indice del giocatore corrente
	int crt,ptss; //valori per la somma dei punti delle carte scoperte
	int bpts;  //punti totali del banco
    int stop; //per il controllo della srtategia del computer
    int punt; //costante per la puntata
    int sball; //variabile per il controllo dela sballata 
    int tavolo; //numero di giocatori
	  // ----parte pubblica----
public:
	void inizio(); //fissa i valori iniziali del gioco
	void mostra_carta(carta tmp,char chi,char coperta);//mostra la carta estratta
	void inserisci_nome(int gnum); //per inserire i nomi dei giocatori
	void strategia(); //permette il gioco del computer
	void giocatori(); //permette di selezionare se la funzione di banco
	                  //sarà svolta dal computer o da un'altra persona
    void partita(int g);      //funzione principale del gioco
	void altra_carta(char men); //richiesta di un'altra carta
    void guarda_carta_coperta(char player); //permette di scegliere se
	                                        //guardare la propria carta coperta
	int punti_scoperte(int ptb); //somma dei punti delle carte scoperte
	                          //del giocatore che servira' per la strategia del computer.
	int mostra_punti(int ptos,int giox);
	int assegna_punteggio(carta cart,char gcat); //assegna il punteggio 
	                                             //alla carta esrtatta	
	int somma_punti(int pt,char dichi,char finale,char cop); //somma i punti delle
	                                                         //carte di ogni giocatore
	int puntata(); //permette e controlla le puntate
};


int setemez::assegna_punteggio(carta cart,char gcat)
{
	int ptot;
 if(gcat=='g') ptot=table[num_gioc].punti; //selezione dell'elenco dei punti totali 		
 else if(gcat=='b') ptot=bpts; //a seconda del giocatore. 

	if(cart.numero==ccg.numero && cart.seme==ccg.seme ||
		cart.numero==ccb.numero && cart.seme==ccb.seme)
					   ptot=0;
int pu;
//assegnamento punteggio alla carta in funzione del valore e anche
//del seme nel caso della Matta
   switch(cart.numero)
   {
	case 1:;case 2:;case 3:;case 4:;case 5:;case 6:;case 7:{pu=(cart.numero*10);};break;
	case 8:;case 9:{pu=5;};break;
   }
	 if(cart.numero==10)
	 {
		if(cart.seme==1) // caso "matta": 10 di denari 
		{    
			//--assegnazione dei punti alla Matta--
  if(ptot==0)pu=5;
  else  if(ptot!=0 && ptot%10==0 && ptot!=70) pu=70-ptot;  
  else if((ptot!=0 && ptot%10!=0 && ptot!=5) || ptot==70) pu=5; 
  else if(ptot==5) pu=70;
		}
		else if(cart.seme==2 || cart.seme==3 || cart.seme==4) pu=5;//Re di altri semi
	 }
	return pu;
}


void setemez::altra_carta(char men)
{
int p;
carta cr;
cr=maz.dai_carta(); //estrae una carta
mostra_carta(cr,men,'s'); //mostra la carta
p=assegna_punteggio(cr,men); //assegnazione del punteggio della carta
	if(men=='g') //se la carta è per il giocatore il punteggio viene
		punti_scoperte(p); //sommato a quello delle carte scoperte
somma_punti(p,men,'u','s'); //il punteggio viene aggiunto ai punti totali del concorrente
 if(men=='g' ||(men=='b' && gio2=='g')) //se il concorrente è 'umano' gli viene chiesto
 {                                      // se stare o se tirare un'altra carta
    char stax;
	cout<<"Stai?\n  Si  s  No n\n";
	cin>>stax;
	if(stax=='n') altra_carta(men);
 }
   system("PAUSE");
}

void setemez::giocatori()
{
cout<<"\n\tScegli chi sara' il banco"
		"\n  'g' ----> per un secondo giocatore \n"
		"  'c' ----> per giocare contro il computer\n";
	cin>>gio2;
	 if(gio2!='c' && gio2!='g') //controllo errori nell'immissione
	 {                          //del tipo di giocatori
		 cout<<"\aGiocatori errati! Reinserisci!\n";
		 giocatori();		 
	 }
}

void setemez::guarda_carta_coperta(char player)
{
char sc;
cout<<"Vuoi vedere la carta coperta?\n Si  s   No  n\n";
cin>>sc;
 if(sc=='s')
 {
 cout<<"La carta nascosta e' "; //se si vuole vedere la propria carta 
 if(player=='g')                //coperta il computer ce la mostra
 mostra_carta(ccg,player,'s');
 else if(player=='b')
 mostra_carta(ccb,player,'s');
 cout<<"\n";
 }
}

void setemez::inizio()
{
	
	cout<<"Quanti giocatori intorno al tavolo?";
    cin>>tavolo;
	if(tavolo>20)tavolo=20; //se viene inserito un numero di giocatori maggiore di 20
	                        //viene fissato ugualmente a 20. 
     for(int tav=0;tav<tavolo;tav++) //per inserire i nomi di tutti i partecipanti
	 {
  	 inserisci_nome(tav);
     table[tav].soldi=300;
	 }
	 giocatori(); //per scegliere se giocare contro il computer oppure
	              //contro un'altra persona
	maz.mescola(); //mescola il mazzo             
	for(int part=0;part<tavolo;part++)
	partita(part);
  //------------------------------------------------------------------------------
  //fine della partita e conclusioni finali.
	int max,nom,equ;
	max=0;
	equ=0;
	if(tavolo>1) //il resoconto dei soldi dei giocatori avviene solo se i giocatori 
	{            //sono più di uno
     for(int y=0;y<tavolo;y++)
	 {
	   if(table[y].soldi>max) //trova il giocatore che ha piu' soldi
	   {
		  max=table[y].soldi;
          nom=y;
	   }
	 }
	
	  for(int z=0;z<tavolo-1;z++) //controlla che i giocatori non  abbiano tutti
		  if(table[z].soldi==table[z+1].soldi) equ++; //lo stesso credito    
   if(equ==tavolo-1 && table[0].soldi==0) 
	   cout<<"Tutti i giocatori hanno finito i soldi!!\n";
   else if(equ==tavolo-1 && table[0].soldi!=0) 
	   cout<<"Avete tutti lo stesso credito!!\n";
   else cout<<"\tCon "<<max<<" soldi "<<table[nom].nome<<" e' il piu' ricco.\n";
	}
 cout<<"\tCiao\n";
   char altra;
   cout<<"Altra partita?\n";
   cin>>altra;
   if(altra=='s') inizio(); //Incomincia una nuova partita come se avessimo 
                            //riavviato il programma.
}

void setemez::inserisci_nome(int gnum)
{
	cout<<"Inserisci nome giocatore "<<gnum+1<<" :";
	cin>>table[gnum].nome;
	strlen(table[gnum].nome);
}


void setemez::mostra_carta(carta tmp,char chi,char coperta)
//'coperta' serve per tenere la carta nascosta evitando il cout
{	
 maz.carte[tmp.numero-1]++; //incremento del parametro per la strategia del computer
 if(coperta=='s') //se la carta non e' coperta viene stampata sullo schermo
 {	
	if(tmp.numero!=ccg.numero && tmp.numero!=ccb.numero
		&& tmp.seme!=ccg.seme && tmp.seme!=ccb.seme) //La scritta "La carta e': " appare
	{                              //solo se la carta non e' una delle due carte coperte
	cout<<"La carta e': ";
	} //Stampa grafica della carta
        cout <<"\n         ÚÄÄÄÄÄÄÄÄ¿";            
        cout <<"\n         ³        ³";
  switch (tmp.numero)                  
  {
  case 1: cout << "\n         ³  Asso  ³";break;
  case 2: cout << "\n         ³  Due   ³";break;
  case 3: cout << "\n         ³  Tre   ³";break;
  case 4: cout << "\n         ³Quattro ³";break;
  case 5: cout << "\n         ³Cinque  ³";break;
  case 6: cout << "\n         ³  Sei   ³";break;
  case 7: cout << "\n         ³ Sette  ³";break;
  case 8: cout << "\n         ³ Fante  ³";break;
  case 9: cout << "\n         ³Cavallo ³";break;
  case 10: cout << "\n         ³   Re   ³";break;
  }
  if(tmp.numero==10 && tmp.seme==1)
  cout<<"La matta!";
          cout <<"\n         ³        ³";   
          cout <<"\n         ³   di   ³    e vale ";
	cout<<assegna_punteggio(tmp,chi)<<" punti per ";
		if(chi=='b')cout<<"il banco";
			else if(chi=='g')cout<<table[num_gioc].nome;
		  cout <<"\n         ³        ³"; 
		  cout <<"\n         ³        ³";
  switch (tmp.seme)                   
  {
  case 1: cout <<"\n         ³Denari  ³";break;
  case 2: cout <<"\n         ³Bastoni ³";break;
  case 3: cout <<"\n         ³ Coppe  ³";break;
  case 4: cout <<"\n         ³ Spade  ³";break;
  }
	 	  cout <<"\n         ³        ³";
		  cout <<"\n         ³        ³";
          cout <<"\n         ÀÄÄÄÄÄÄÄÄÙ";					   
 }
}

int setemez::mostra_punti(int ptos,int giox) //mostra i punti del giocatore selezionato
{
	if(giox=='b') //se è il banco
cout<<"Il banco ha totalizzato "<<ptos<<" punti.\n";
	else if(giox=='g') //se è un giocatore
cout<<table[num_gioc].nome<<" ha totalizzato "<<ptos<<" punti.\n";
return ptos;
}

void setemez::partita(int g)
{ 
   
            if(table[g].soldi>10) //La partita viene effettuata solo se il giocatore  
				          //numero 'g' ha un credito sufficiente per giocare.
			{
	cout<<"\tPartita di "<<table[g].nome<<"------>>\n"; 
 //--fase di inizializzazione della partita--
	num_gioc=g;
	table[g].soldi=table[g].soldi-10;   //10 soldi per il piatto.
	sball=0; //riporta il parametro per il controllo della sballata
	         //ai valori "iniziali"
	bpts=0; //punti totali del banco e
    table[g].punti=0; //del giocatore con valore iniziale zero
    ptss=0; //punti iniziali delle carte scoperte uguale a zero a cui
	        //si andranno a sommare i punti delle carte che usciranno
	        //dopo la prima carta coperta del giocatore
		crt=0; //ancora non è il momento di sommare le carte scoperte
 //--inizio delle azioni--
cout<<"Estratta 1° carta di "<<table[g].nome<<".\n";     //estrae le prime due carte
ccg=maz.dai_carta();                                     //coperte e le memorizza per
somma_punti(assegna_punteggio(ccg,'g'),'g','u','c');     //eventuali controlli
cout<<"Estratta 1° carta del banco.\n";                  //successivi.
ccb=maz.dai_carta();                                     //               
somma_punti(assegna_punteggio(ccb,'b'),'b','u','c');        
crt=1; //fa partire la somma dei punti delle carte scoperte del giocatore.
ptss=0; //punti iniziali delle carte scoperte.
stop=0;
cout<<"             Gioca "<<table[g].nome<<"---->\n";
 guarda_carta_coperta('g'); //viene chiesto se si vuole vedere la propria carta coperta.
puntata(); //viene chiesto al giocatore di puntare.
cout<<" stai?\n";
char gst;
cin>>gst;
  if(gst=='n') //se al giocatore non vanno bene i punti  della carta
               //coperta parte altra_carta() per richiedere altre carte
        altra_carta('g'); //--giocata del giocatore-- 
  else if(gst=='s') //se il giocatore add un certo punto decide di stare.. 
  {
   if(sball==0)  //..e se il giocatore non ha sballato..
   {                 
	 if(gio2=='g')  //..parte la giocata del banco
	 {                 
		 cout<<"        Gioca il banco---->\n";
		 guarda_carta_coperta('b');
	  cout<<"Banco stai?\n";
	  char bst;
	  cin>>bst;

	  if(bst=='n') //se il banco è umano parte la giocata del banco
	  {           
           altra_carta('b');
	  }	
	 }
	 else if(gio2=='c') //se invece si gioca contro il computer parte 
                        //la strategia del computer
	 { 
		 cout<<"Gioca COMPUTER--->\n";
       while(stop!=1)                
	   {                 
		 strategia();
	   }
	 }
   }
  }
  cout<<"\t                *******---------------------*******\n";//denota la schermata  
  //delle conclusioni finali della partita.
  mostra_punti(table[g].punti,'g'); //mostra ipunti del giocatore
  mostra_punti(bpts,'b'); //mostra i punti del banco
  switch(sball) //se il giocatore ha sballato la giocata del banco
	            //non parte e si va subito alle conclusioni finali
  {
	  case 1: //ha sballato il banco quindi ha vinto il giocatore.
		  {
			  cout<<"\t**-------------------->>Ha vinto "<<table[g].nome;
				  cout<<" con "<<table[g].punti<<" punti!\n";
			  table[g].soldi=table[g].soldi+punt;
		  };
		  break;
	  case 2: //ha sballato il giocatore quindi ha vinto il banco.
		  {
			  cout<<"\t**-------------------->>Ha vinto il banco"
				  " con "<<bpts<<" punti!\n";
			  table[g].soldi=table[g].soldi-punt;
		  };
		  break;
	  default:
		      //se nessuno ha sballato si confrontano i punti e si 
		  {   //arriva alle conclusioni finali.
		   if(bpts<table[g].punti)
		   {
			  cout<<"\t**-------------------->>Ha vinto "<<table[g].nome;
				  cout<<" con "<<table[g].punti<<" punti!\n";
			  table[g].soldi=table[g].soldi+punt;
		   }
		   else if(bpts>table[g].punti || bpts==table[g].punti)
		   {
			  cout<<"\t**-------------------->>Ha vinto il banco" 
				  " con "<<bpts<<" punti!\n";
			  table[g].soldi=table[g].soldi-punt;
		   };
		  break; 
		  }
  }   
  cout<<"La carta coperta del banco era ";
  mostra_carta(ccb,'b','s'); 	
   if(table[g].soldi==0)cout<<"\n"<<table[g].nome<<" hai finito i soldi!\n"; 
   //controllo per il credito rimasto  
   else cout<<"\n"<<table[g].nome<<" hai ancora "<<table[g].soldi<<" soldi\n";
   if(maz.matta==1)
   {
	  maz.mescola();  //rimescola il mazzo se e' uscita la matta.
    for(int nit=0;nit<10;nit++)
	maz.carte[nit]=0;
   }
 if(g==tavolo-1)
 {
  cout<<"Vuoi continuare a giocare?\n";
  char part;
  cin>>part;
   if(part=='s') //permette di cambiare giocatore e quindi di riportare
   {             //il credito disponibile al valore iniziale ( 300 )
	   cout<<"Cambio dei giocatori?\n";
		   char change;
	   cin>>change;
	   if(change=='s')
	   { //Se si ha intenzione di cambiare i partecipanti o di ricominciare da capo
         //viene mostrata una tabella con il resoconto dei crediti ottenuti dai
		 //partecipanti della partita abbandonata.
		   cout<<"Resoconto punti:\n";
		   int mezz;
		   if(tavolo%2==0) mezz=tavolo/2;
		   else if(tavolo%2!=0) mezz=(tavolo-1)/2;
		   for(int fint=0;fint<mezz;fint++)
		   {
			   cout<<table[fint].nome<<"--->"<<table[fint].soldi;
			   cout<<"                    "<<table[fint+mezz].nome;
		       cout<<"--->"<<table[fint+mezz].soldi<<"\n";
		   }
		    if(tavolo%2!=0) 
			{
			   cout<<table[tavolo-1].nome<<"--->"<<table[tavolo-1].soldi<<"\n";
			}
		   	inizio();

	   }	for(int game=0;game<tavolo;game++)
	partita(game); //se si vuole cotinuare a giocare parte una nuova partita
   }
 }
             } //chiusura 'if(table[g].soldi>10)...'
}

int setemez::puntata()
{		
 cout<<"Hai ancora "<<table[num_gioc].soldi<<" soldi\n";
 cout<<"Quanto punti?\n";	 
 cin>>punt;
 if(punt>table[num_gioc].soldi) //controllo del credito disponibile
 {
	 cout<<"Non hai abbastanza soldi! Ripunta!"
		 " Massimo "<<table[num_gioc].soldi<<" soldi.\n";
 puntata(); 
 }
 else       //ritorna il valore della puntata solo se  
   	return punt;   //è statoinserito un valore esatto.
}

int setemez::punti_scoperte(int ptb)
{
	if(crt==1) //serve a non includere nella somma le prime due carte coperte
	{   
		ptss=ptss+ptb;
	}	
return ptss; //ritorna i punti totali delle carte scoperte del giocatore
}
				
int setemez::somma_punti(int pt,char dichi,char finale,char cop)
{	
	int ptots; 
		if(dichi=='b')
		{                  //somma dei punti del banco
			 bpts=bpts+pt; // 			
			 ptots=bpts;   //	
	 if(ptots>75) //se il banco sballa viene avvisato.
	 {
		 cout<<"\a\n      Il banco ha sballato!\n";
		 sball=1; //variabile per il controllo dello sballo
	 }	
	 if(cop=='s') //'cop' evita il cout dei punti se la carta e' coperta
	 {
  cout<<"\n                           Il banco ha  "<<bpts<<"  punti\n";
	 }
		}
	else if(dichi=='g')
	{                //somma dei punti del giocatore
		table[num_gioc].punti=table[num_gioc].punti+pt;	 	
		ptots=table[num_gioc].punti;		
if(ptots>75) //se il giocatore sballa viene avvisato.
{
	cout<<"\a\n       Il giocatore ha sballato!\n";
	sball=2; //variabile per il controllo dello sballo
}
if(cop=='s') //'s' sta per "carta Scoperta"
{	
cout<<"\n                           "<<table[num_gioc].nome<<" hai"
"  "<<table[num_gioc].punti<<"  punti\n";
}
	}
return ptots;	
}                 

void setemez::strategia() //la strategia tiene conto delle carte uscite mediante
                          //l'array  'carte[10]'  della classe 'mazzo'.
{
 int ptgr; 
 int incr,ctr;
 ptgr=0; //serve per il controllo delle probabilità
  if(bpts<=ptss || (ptss==0 && bpts<50))
  {
		if(bpts%10==0 && bpts!=70) //punti del banco multipli di 10
		{			
		 incr=((bpts)/10)-1; //il valore di 'incr' parte dal valore del punteggio 
		 ctr=7-incr;              //ottenuto finora
		    //dal banco(-1 poichè verrà utilizzato come indice nell'array 'carte[10]').
		  while(incr<7)
		  {   //Controllo della probabilità che escano carte che possano far sballare
			 ptgr=ptgr+maz.carte[incr]; //il banco.
			 incr++;
		  }
			if((ptgr>(ctr*2))||(ptss==0 && bpts<50)) 
			{
				altra_carta('b');//se le probabilità calcolate sono accettabili il 
			}	             //computer richiede un'altra carta
			else stop=1;
		}
	 else if(bpts%10!=0 && bpts!=70) //punti del banco non multipli di 10
	 {		 
		 incr=((bpts-5)/10)-1;
		 ctr=7-incr;
		 while(incr<7)
		 {
			 ptgr=ptgr+maz.carte[incr];
			 incr++;	 
		 }
		  if((ptgr>(ctr*2))||(ptss==0 && bpts<50))
		  {
			  altra_carta('b');
		  }
		  else stop=1;
	 }
	 else if(bpts==70)
	 {
		 int fig;
		 fig=0;
		 for(int gtr=8;gtr<10;gtr++) //calcola la probanilità che esca una
         fig=fig+maz.carte[gtr]; //figura per arrivare a sette e mezzo senza
	  if((fig<6)||(ptss==0 && bpts<50)) //sballare.
	  {
		 altra_carta('b');
	  }
	  else stop=1;
	 }	
  }
   else stop=1;
}

//                     **----main----**
main()
{
cout<<"\n\n\n"
"                         Benvenuti al gioco del 7&1/2\n"
"                              di Giorgio Cerrito\n\n";
cout <<"\nVuoi leggere le regole  del gioco?       Si   's'  No   'n'\n";
cout <<"\n>>---->";
char regole;
cin >>regole;
if(regole=='s')
{                     //              ---regole---
cout<<"\nÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿";
cout<<"\n³                      ----->Regole del gioco<-----                           ³";
cout<<"\n³Il sette e mezzo e' un gioco di carte abbastanza semplice. Lo ''scontro''    ³";
cout<<"\n³avviene tra due utenti: un Banco ed un Giocatore. Lo scopo del gioco e'      ³";
cout<<"\n³avvicinarsi il piu' possibile al punteggio di sette e mezzo, senza superarlo ³";
cout<<"\n³(cioe'senza sballare).La prima carta del banco e del giocatore si tengono    ³";
cout<<"\n³coperte. Durante il gioco si possono richiedere altre carte fino a quando non³";
cout<<"\n³si decide di fermarsi (STARE) o si ha sballato.                              ³";
cout<<"\n³Per calcolre i punti si ricorda che:                                         ³";
cout<<"\n³-le carte da 1 a 7('svestite') hanno il punteggio equivalente al loro valore;³";
cout<<"\n³-le restanti('figure':Fante, Cavallo e Re) valgono mezzo punto, ad eccezione ³";
cout<<"\n³della MATTA (re di Denari):                                                  ³";
cout<<"\n³-se il giocatore ha gia' in mano una figura essa vale SETTE in modo tale da  ³";
cout<<"\n³ raggiungere SETTE E MEZZO.                                                  ³";
cout<<"\n³-se la matta e' la prima carta del giocatore essa vale solo mezzo PUNTO anche³";
cout<<"\n³ quando si pesca una carta successiva.                                       ³";
cout<<"\n³-se il giocatore gia' possiede una carta 'svestita'la matta sara'uguale al   ³";
cout<<"\n³ valore necessario per raggiungere SETTE, e rimarra' di questo valore anche  ³";
cout<<"\n³ quando sara' pescata la carta successiva, con la speranza che essa sia una  ³";
cout<<"\n³ figura altrimenti si sballa.                                                ³";
cout<<"\n³Dopo aver concluso la fase di distribuzione delle prime carte, si comincia il³";
cout<<"\n³gioco; il banco vince se possiede un punteggio uguale o maggiore di quello   ³";
cout<<"\n³del gicatore.                                                                ³";
cout<<"\nÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n";
}
	setemez set; //variabile di tipo 'setemez' 
	//---incomincia la prima partita---
    set.inizio(); //inizializza le variabibli con il valore iniziale e mescola il mazzo.
    return 0;
}


