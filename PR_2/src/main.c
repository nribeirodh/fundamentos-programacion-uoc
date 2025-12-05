#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_SUPPORTERS 3 //Nº AFICIONADOS
#define BASE_MEMBERSHIP_YEARS 5 //MAX AÑOS DE MEMBRESÍA BASE
#define SILVER_MEMBERSHIP_YEARS 10 // MAX AÑOS MEMBRESÍA SILVER
#define BASE_MEMBERSHIP_POINTS 10 //PUNTOS MEMBRESÍA BASE
#define SILVER_MEMBERSHIP_POINTS 15 //PUNTOS MEMEBRESÍA SILVER
#define GOLD_MEMBERSHIP_POINTS 20 //PUNTOS MEMBRESÍA GOLD 
#define RECORDS_PENALTY_POINTS 5 //PENALIZACIÓN PUNTOS
#define MAX_NAME 25 //MÁXIMO CARACTERES NOMBRE

typedef enum{BASE=1, SILVER, GOLD} tMembershipType;

typedef struct{
    char name[MAX_NAME];
    int age;
    int membershipYears;
    bool hasRecords;
    } tSupporter;
    
// Función para copiar datos de un aficionado a otro
void supporterCpy(tSupporter *supporterDst, tSupporter supporterSrc) {
    strcpy(supporterDst->name, supporterSrc.name);//copiamos los datos de un aficionado a otro
    supporterDst->age = supporterSrc.age;
    supporterDst->membershipYears = supporterSrc.membershipYears;
    supporterDst->hasRecords = supporterSrc.hasRecords;
    }
    
//Ejercicio 2.1, función p/ obtener la membresía
tMembershipType getMembershipType(int membershipYears){
    tMembershipType result;
    if(membershipYears <= BASE_MEMBERSHIP_YEARS){
        result=BASE;
        }
        else if(membershipYears<=SILVER_MEMBERSHIP_YEARS){
            result=SILVER;
            }
            else{
                result=GOLD;
                }
    return result;
    }
//ejercicio 2.2 accion para leer los datos
void readSupporter(tSupporter *supporter){
    char name[MAX_NAME];
    int hasRecords; //aux
    printf("NAME (25 CHAR MAX, NO SPACES)?\n");
    scanf("%s", name);
    printf("AGE (AN INTEGER)?\n");
    scanf("%d", &supporter->age);
    printf("MEMBERSHIP YEARS (AN INTEGER)?\n");
    scanf("%d", &supporter->membershipYears);
    printf("HAS RECORDS (0-FALSE, 1-TRUE)?\n");
    scanf("%d", &hasRecords);
    strcpy(supporter->name, name);
    supporter->hasRecords = (bool)hasRecords;
    }

//ejercio 2.3 accion para imprimir los datos del resultado 
void writeSupporter(tSupporter supporter){
    printf("NAME: %s\n", supporter.name);
    printf("AGE: %d\n", supporter.age);
    printf("MEMBERSHIP YEARS: %d\n", supporter.membershipYears);
    if(supporter.hasRecords){
        printf("HAS RECORDS (0-FALSE, 1-TRUE): 1\n");
        }
        else{
            printf("HAS RECORDS (0-FALSE, 1-TRUE): 0\n");
            }
            printf("MEMBERSHIP TYPE (1-BASE, 2-SILVER, 3-GOLD): %d\n", getMembershipType(supporter.membershipYears));
            printf("POINTS: %d\n", getPoints(supporter));
    }

//ejercicio 2.4 funcion para calcular los puntos de un aficionado
int getPoints(tSupporter supporter){
    int result;
    tMembershipType mSupporter;
    mSupporter = getMembershipType(supporter.membershipYears);

    if(mSupporter == BASE){
        result = BASE_MEMBERSHIP_POINTS;
        }
        else if(mSupporter == SILVER){
            result = SILVER_MEMBERSHIP_POINTS;
            }
            else{
                result = GOLD_MEMBERSHIP_POINTS;
                }
                
    if (supporter.hasRecords){
        result = result - RECORDS_PENALTY_POINTS;
        }
    return result;
    }
    
    int main(int argc, char **argv)
{
    tSupporter supporters[NUM_SUPPORTERS]; 
    tSupporter selectedSupporter; // aficionado seleccionado
    int i;

    // ejercicio 2.5
    printf("INPUT DATA\n");
    for(i = 1; i <= NUM_SUPPORTERS; i++){
        readSupporter(&(supporters[i-1]));
    }

    // ejercicio 2.6
    //seleccionamos al primer aficionado
    supporterCpy(&selectedSupporter, supporters[0]);

    for (i = 2; i <= NUM_SUPPORTERS; i++) {
        if(getPoints(selectedSupporter) < getPoints(supporters[i-1])){
            supporterCpy(&selectedSupporter, supporters[i-1]);
            }
            else if(getPoints(selectedSupporter) == getPoints(supporters[i-1])){ 
                //en caso de empate en puntos, se compara el número de años de membresía
                if(selectedSupporter.membershipYears < supporters[i-1].membershipYears){
                    supporterCpy(&selectedSupporter, supporters[i-1]);
                    }
                }
        }
    printf("SELECTED SUPPORTER\n");
    writeSupporter(selectedSupporter);
    return 0;
}

