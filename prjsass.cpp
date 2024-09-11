#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_ETD 100
#define NUM_DEP 3
char departements[3][50] = {"departement1","departement2","departement3"};

typedef struct tm date;
typedef struct {
	char id[7];
	char nom[30];
	char prenom[30];
	date dn; //date de naissance
	char dp[50]; // departement
	float note;
} etudiant;

typedef struct {
	etudiant tab[MAX_ETD]; // tableau des etudiants
	int l; // nombre des etudiants
} list_etd;

char * num_to_str(int n);
void ajouter_etd(list_etd * list, etudiant e);
list_etd init_list();
void afficher_tout(list_etd list);
void insertion_par_defaut(list_etd * list);
int rechercher_etd(list_etd list, char*id);
void supprimer_etd(list_etd * list,char * id);
void modifier_etd(list_etd * list , char *id);
void afficher_etd(list_etd list,char * id);
float moyen_dp(list_etd list,char * dp);
int nombre_etd(list_etd list);
int nombre_dp(list_etd list, char* dp);
float moyen_univers(list_etd list);
void afficher_sup(list_etd list , float n);
int reussir_dp(list_etd list,char* dp);


int main() {
	srand(time(NULL));
	list_etd list = init_list();
	
	int choice;
	char id[7];
	do {
        printf("\nMenu:\n");
        printf("1. insertion par defaut\n");
        printf("2. Afficher tout\n");
        printf("3. ajouter Etudiant\n");
        printf("4. supprimer par id\n");
        printf("5. Afficher Etudiant\n");
        printf("6. modifier Etudiant\n");
        printf("7. calculer moyenne d un departement\n");
        printf("8. nombre des etudiants existants\n");
        printf("9. nombre des etudiants d un departement\n"); 
        printf("10. la moyenne de l universite\n");
        printf("11. les etudiant ayant une moyenne superieur a un seuil\n");
        printf("12. les etudiant d un departement qui ont reussi\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                insertion_par_defaut(&list);
                printf("Default students inserted.\n");
                break;
            case 2:
                afficher_tout(list);
                break;
            case 3:
            	etudiant e;
            	char nom[30];
	        	char prenom[30];
	         	date dn;
	         	int day;
	        	int mon;
	        	int year;
	        	char dp[50];
	         	float note;
	        	printf("\n donner le nom :\n");
		        scanf(" %s",nom);
		        printf("\n donner le prenom :\n");
		        scanf(" %s",prenom);
		        printf("\n donner la date de naissance :\n");
		        printf("\n donner l annee :\n");
		        scanf(" %d",&year);
		        dn.tm_year = year-1900;
		        printf("\n donner le mois :\n");
		        scanf(" %d",&mon);
		        dn.tm_mon = mon-1;
		        printf("\n donner le jour :\n");
		        scanf(" %d",&day);
		        dn.tm_mday = day;
		        printf("\n donner le departement :\n");
		        scanf(" %s",dp);
		        printf("\n donner la note generale :\n");
	        	scanf(" %f",&note);
            	strcpy(e.nom,nom);strcpy(e.prenom,prenom);strcpy(e.dp,dp);e.dn=dn ;e.note = note;
            	ajouter_etd(&list, e);
            	break;
            case 4:
                printf("Enter the ID of the student to delete: ");
                scanf("%s", id);
                supprimer_etd(&list, id);
                printf("Student with ID %s deleted.\n", id);
                break;
            case 5:
            	char id[7];
            	printf("\ndonner l id:\n");
            	scanf("%s",id);
            	printf("\n");
            	afficher_etd(list,id);
            	break;

            case 6:
			    printf("donner l id de l'etudiant a modifier\n");
				scanf("%s",id);
				modifier_etd(&list,id); 
				break;
			case 7:
				int num;
				float moyen;
				printf("choisissez un departement ex: 1 :\n");
				for(int i =0;i<NUM_DEP;i++) {
					printf("%d-%s\n",i+1,departements[i]);	
				}
				scanf("%d",&num);
				moyen = moyen_dp(list,departements[num-1]);
				printf("\nla moyenne du departement %s est : %.2f\n",departements[num-1],moyen);
			break;
			case 8:
				printf("le nombre des etudiant existants est : %d \n :",nombre_etd(list));
			break;
			case 9:
				printf("choisissez un departement ex: 1 :\n");
				for(int i =0;i<NUM_DEP;i++) {
					printf("%d-%s\n",i+1,departements[i]);	
				}
				scanf("%d",&num);
				printf("le nombre des etudiants de departement %s est : %d \n",departements[num-1],nombre_dp(list,departements[num-1]));
			break;
			case 10:
				printf("la moyenne de l universite est : %.2f",moyen_univers(list));
			break;
			case 11 :
			    float seuil; 
			    printf("entrer un seuil\n");
				scanf("%f",&seuil);
				afficher_sup(list,seuil);
			break;
			case 12 :
				printf("donner numero d un departement\n");
				for(int i =0;i<NUM_DEP;i++) {
					printf("%d-%s\n",i+1,departements[i]);	
				}
				scanf("%d",&num);
				printf("le nombre des etudiants qui ont reussi dans ce departement est : %d \n",reussir_dp(list,departements[num-1]));
			break;	
			case 14:
                printf("Exiting...\n");
            break;	
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 8);
	
	return 0;
}


char* num_to_str(int n){
	char *t;
	int mod;
	int m = n;
	int l=0;
	if (n == 0) {
    t = (char*)malloc(2);
    t[0] = '0';
    t[1] = '\0';
    return t;
    }
	while(m) {
		mod = n % 10;
		m/=10;
		l++;
	}
	t=(char*)malloc(l+1);
	for(int i=l-1;i>=0;i--){
		t[i]=(n%10)+'0';
		n/=10;
	}
	t[l]='\0';
	return t;
}



void ajouter_etd(list_etd * list, etudiant e){	
	int l = list->l;
	if(l>=MAX_ETD) {
		printf("la liste est pleine\n");
		return;
	}
	int r = 100000+rand()%899999;
	strcpy(e.id,num_to_str(r));
	list->tab[l]=e;
	list->l++;
	return;
}
list_etd init_list() {
	list_etd list;
	list.l = 0;
	return list;
}

void afficher_tout(list_etd list){
	for(int i = 0;i<list.l;i++) {
		printf("\n etudiant %d\n :",i+1);
		printf("id : %s \n",list.tab[i].id);
		printf("nom : %s \n",list.tab[i].nom);
		printf("prenom : %s \n",list.tab[i].prenom);
		printf("date de naissance : (%d/%02d/%02d)\n",list.tab[i].dn.tm_year+1900,list.tab[i].dn.tm_mon+1,list.tab[i].dn.tm_mday);
		printf("departement : %s \n",list.tab[i].dp);
		printf("note general : %.2f \n\n",list.tab[i].note);
	}
}
void insertion_par_defaut(list_etd * list) {
	etudiant e1;
	strcpy(e1.nom,"yassine");strcpy(e1.prenom,"snaiki");strcpy(e1.dp,"departement2");e1.dn.tm_year = 101;	e1.dn.tm_mon = 8;e1.dn.tm_mday = 29, e1.note = 10.25;
	etudiant e2;
	strcpy(e2.nom,"etudiant2_nom");strcpy(e2.prenom,"etudiant2_prenom");strcpy(e2.dp,"departement1");e2.dn.tm_year = 102;	e2.dn.tm_mon = 5;e2.dn.tm_mday = 19, e2.note = 12;
	etudiant e3;
	strcpy(e3.nom,"etudiant3_nom");strcpy(e3.prenom,"etudiant3_prenom");strcpy(e3.dp,"departement2");e3.dn.tm_year = 102;	e3.dn.tm_mon = 2;e3.dn.tm_mday = 6,e3.note = 15.5;
	etudiant e4;
	strcpy(e4.nom,"etudiant4_nom");strcpy(e4.prenom,"etudiant4_prenom");strcpy(e4.dp,"departement3");e4.dn.tm_year = 102;	e4.dn.tm_mon = 5;e4.dn.tm_mday = 19,e4.note = 7.75;
	etudiant e5;
	strcpy(e5.nom,"etudiant5_nom");strcpy(e5.prenom,"etudiant5_prenom");strcpy(e5.dp,"departement3");e5.dn.tm_year = 100;	e5.dn.tm_mon = 7;e5.dn.tm_mday = 10,e5.note = 17.75;
	etudiant e6;
	strcpy(e6.nom,"etudiant6_nom");strcpy(e6.prenom,"etudiant6_prenom");strcpy(e6.dp,"departement2");e6.dn.tm_year = 102;	e6.dn.tm_mon = 5;e6.dn.tm_mday = 15,e6.note = 12;
	etudiant e7;
	strcpy(e7.nom,"etudiant7_nom");strcpy(e7.prenom,"etudiant7_prenom");strcpy(e7.dp,"departement1");e7.dn.tm_year = 99;	e7.dn.tm_mon = 11;e7.dn.tm_mday = 5,e7.note = 10;
	etudiant e8;
	strcpy(e8.nom,"etudiant8_nom");strcpy(e8.prenom,"etudiant8_prenom");strcpy(e8.dp,"departement1");e8.dn.tm_year = 101;	e8.dn.tm_mon = 0;e8.dn.tm_mday = 13,e8.note = 9;
	etudiant e9;
    strcpy(e9.nom,"etudiant9_nom");strcpy(e9.prenom,"etudiant9_prenom");strcpy(e9.dp,"departement3");e9.dn.tm_year = 103; e9.dn.tm_mon = 6; e9.dn.tm_mday = 24, e9.note = 11.5;

    etudiant e10;
    strcpy(e10.nom,"etudiant10_nom");strcpy(e10.prenom,"etudiant10_prenom");strcpy(e10.dp,"departement2");e10.dn.tm_year = 101; e10.dn.tm_mon = 9; e10.dn.tm_mday = 30, e10.note = 14.75;

    etudiant e11;
    strcpy(e11.nom,"etudiant11_nom");strcpy(e11.prenom,"etudiant11_prenom");strcpy(e11.dp,"departement1");e11.dn.tm_year = 104; e11.dn.tm_mon = 2; e11.dn.tm_mday = 12, e11.note = 13.25;

    etudiant e12;
    strcpy(e12.nom,"etudiant12_nom");strcpy(e12.prenom,"etudiant12_prenom");strcpy(e12.dp,"departement3");e12.dn.tm_year = 99; e12.dn.tm_mon = 10; e12.dn.tm_mday = 19, e12.note = 9.5;

    etudiant e13;
    strcpy(e13.nom,"etudiant13_nom");strcpy(e13.prenom,"etudiant13_prenom");strcpy(e13.dp,"departement1");e13.dn.tm_year = 98; e13.dn.tm_mon = 3; e13.dn.tm_mday = 5, e13.note = 16;

    etudiant e14;
    strcpy(e14.nom,"etudiant14_nom");strcpy(e14.prenom,"etudiant14_prenom");strcpy(e14.dp,"departement2");e14.dn.tm_year = 100; e14.dn.tm_mon = 8; e14.dn.tm_mday = 8, e14.note = 7.25;
    
    etudiant e15;
    strcpy(e15.nom,"etudiant15_nom");strcpy(e15.prenom,"etudiant15_prenom");strcpy(e15.dp,"departement3");e15.dn.tm_year = 102; e15.dn.tm_mon = 4; e15.dn.tm_mday = 21, e15.note = 18.5;

    etudiant e16;
    strcpy(e16.nom,"etudiant16_nom");strcpy(e16.prenom,"etudiant16_prenom");strcpy(e16.dp,"departement1");e16.dn.tm_year = 101; e16.dn.tm_mon = 1; e16.dn.tm_mday = 11, e16.note = 8;

	
	ajouter_etd(list,e1);
	ajouter_etd(list,e2);
	ajouter_etd(list,e3);
	ajouter_etd(list,e4);
	ajouter_etd(list,e5);
	ajouter_etd(list,e6);
	ajouter_etd(list,e7);
	ajouter_etd(list,e8);
	ajouter_etd(list,e9);
	ajouter_etd(list,e10);
	ajouter_etd(list,e11);
	ajouter_etd(list,e12);
	ajouter_etd(list,e13);
	ajouter_etd(list,e14);
	ajouter_etd(list,e15);
	ajouter_etd(list,e16);
}
int rechercher_etd(list_etd list , char* id){
	for(int i=0;i<list.l;i++) {
		if(!strcmp(list.tab[i].id,id)) return i;
	}
	printf("etudiant non trouvé\n\n");
	return -1;
}

void supprimer_etd(list_etd * list, char * id) {
	int index = rechercher_etd(*list,id);
	char rep;
	
	
	if(index>=0){
		printf("vous etes sure ? (y/n) \n ");
     	scanf(" %c",&rep);
    	if(rep == 'y') {
    		for(int i = index;i<list->l-1;i++){
	     	list->tab[i] = list->tab[i+1];
      	}
      	list->l--;
		}
		
	}	
}

void modifier_etd(list_etd* list,char *id) {
	char rep;
	int index = rechercher_etd(*list,id);
	if(index>=0) {
		char nom[30];
		char prenom[30];
		date dn;
		int mon;
		int year;
		char dp[50];
		float note;
		printf("\nmodifier le nom :\n");
		scanf(" %s",nom);
		printf("\nmodifier le prenom :\n");
		scanf(" %s",prenom);
		printf("\nmodifier la date de naissance :\n");
		    printf("\nmodifier l annee :\n");
		    scanf(" %d",&year);
		    dn.tm_year = year-1900;
		    printf("\nmodifier le mois :\n");
		    scanf(" %d",&mon);
		    dn.tm_mon = mon-1;
		    printf("\nmodifier le jour :\n");
		    scanf(" %d",&dn.tm_mday);
		printf("\nmodifier le departement :\n");
		scanf(" %s",dp);
		printf("\nmodifier la note generale :\n");
		scanf(" %f",&note);
		getchar();
		printf("\nappliquer la modification? (y/n)\n");
		scanf(" %c",&rep);
		if(rep=='y') {
			strcpy(list->tab[index].nom,nom);
		    strcpy(list->tab[index].prenom,prenom);
		    list->tab[index].dn = dn;
		    strcpy(list->tab[index].dp,dp);
		    list->tab[index].note=note;
		}
	}
}

void afficher_etd(list_etd list,char * id) {
	int index = rechercher_etd(list , id);
	if(index>=0) {
		printf("id : %s \n",list.tab[index].id);
		printf("nom : %s \n",list.tab[index].nom);
		printf("prenom : %s \n",list.tab[index].prenom);
		printf("date de naissance : (%d/%02d/%02d)\n",list.tab[index].dn.tm_year+1900,list.tab[index].dn.tm_mon+1,list.tab[index].dn.tm_mday);
		printf("departement : %s \n",list.tab[index].dp);
		printf("note general : %.2f \n\n",list.tab[index].note);
		return;
	}
	printf("\n etudiant n existe pas\n");
}
float moyen_dp(list_etd list, char* dp) {
	int l = list.l;
	int count=0;
	float sum=0;
	int i;
	for(i =0;i<l;i++) {
		if(!strcmp(list.tab[i].dp,dp)){
		sum += list.tab[i].note;
		count++;	
		}
	} 
	return count>0 ? (float)sum/(float)count : 0;
}
float moyen_univers(list_etd list) {
	int l = list.l;
	int sum=0;
	int i;
	for(i =0;i<l;i++) {
	
		sum += list.tab[i].note;	
		
	} 
	return l>0 ? (float)sum/l : 0;
}
int nombre_etd(list_etd  list) {
	return list.l;
}
int nombre_dp(list_etd list, char* dp){
	int sum=0;
	int l = list.l;
	for(int i =0;i<l;i++) {
		if(!strcmp(list.tab[i].dp,dp)){
		sum ++;	
		}
	} 
	return sum;
}

void afficher_sup(list_etd list , float n) {
	int j= 1;
	for(int i = 0;i<list.l;i++) {
		if(list.tab[i].note>=n){
			printf("etudiant %d\n",j++);
	     	afficher_etd(list,list.tab[i].id);
		}		
	}
}

int reussir_dp(list_etd list,char* dp) {
	int sum = 0;
	for(int i= 0;i<list.l;i++) {
		if(list.tab[i].note>=10 && !strcmp(list.tab[i].dp,dp)) {
			sum++;
		}
	}
	return sum;
}

void top3(list_etd list) {
	
}


