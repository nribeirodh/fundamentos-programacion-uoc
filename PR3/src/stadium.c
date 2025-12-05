#include <stdlib.h>
#include <string.h>
#include "stadium.h"

/* Auxiliary Actions */

/* Copy ticket structure */
void ticketCpy(tTicket *dst, tTicket src)
{
    dst->eventType= src.eventType;
	dst->price = src.price;
}

/* Copy supporter structure */
void supporterCpy(tSupporter *dst, tSupporter src) 
{    
    int i;
	dst->id = src.id;
    strcpy(dst->name,src.name);
	dst->age = src.age;
	dst->membershipYears = src.membershipYears;	
	dst->tickets.nTickets = src.tickets.nTickets;
    for (i = 0; i < src.tickets.nTickets; i++) {
        ticketCpy(&dst->tickets.table[i],src.tickets.table[i]);		
	}
}

/* The content of the string str is parsed into the fields of the supporter structure */
void getSupporterObject(const char *str, tSupporter *supporter) 
{
    /* read suporter data */
    sscanf(str, "%d %s %d %d %d", &supporter->id, supporter->name, &supporter->age, &supporter->membershipYears, &supporter->tickets.nTickets);
}

/* The content of the string str is parsed into the fields of the ticket structure */
void getTicketObject(const char *str, tTicket *ticket) 
{
	int auxEventType;
	
    /* read tTicket data */
    sscanf(str, "%d %f", &auxEventType, &ticket->price);
	ticket->eventType = (tEventType)auxEventType;
}

/* Load supporters's table from file */
void supportersTableLoad(tSupporterTable *tabSupporters, const char* filename, tError *retVal){
	FILE *fin=NULL;
	char line[MAX_LINE];
	tSupporter newSupporter;
	int i;
	
	*retVal = OK;	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {
		/* Read all the supporters */
		while(!feof(fin) && tabSupporters->nSupporters < MAX_SUPPORTERS && *retVal == OK) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line) > 1) {
				/* Get data supporter */
				getSupporterObject(line, &newSupporter);	
				
				/* Load all supporter's tickets */
                for (i = 0; i < newSupporter.tickets.nTickets; i ++) {		
					line[0] = '\0';
                    fgets(line, MAX_LINE-1, fin);
                    line[MAX_LINE-1]='\0';
                    if(strlen(line) > 1) {	
						/*Get data screen */					
                        getTicketObject(line, &newSupporter.tickets.table[i]);						
					}
				}
				/* Add the new supporter to the output table */                
				supporterTableAdd (tabSupporters, newSupporter, retVal);			
			}			
		}	
		/* Close the file */
		fclose(fin);	
	}
	else {
		*retVal = ERR_CANNOT_READ;
	}	
}

/* Write a table supporters */
void writeTabSupporters(tSupporterTable tabSupporters) {
	int i;
	printf("ID NAME           AGE\n");
	printf("=====================\n");				
	for (i = 0; i < tabSupporters.nSupporters; i++){
		printf("%-2d %-15s %2d\n",tabSupporters.table[i].id, tabSupporters.table[i].name, tabSupporters.table[i].age);			
	}	
	printf("\n");
}

/* Write a ticket */
void writeTicket(tTicket ticket) {
	printf("\n");
	printf("EVENT TYPE (1-FOOTBALL MATCH, 2-CONCERT, 3-EXPO): %u\n", ticket.eventType);
	printf("PRICE [EUR]: %.2f\n", ticket.price);
}

/* Select a supporter from a table supporters by ID */
void selectSupporter (tSupporterTable tabSupporters, int supporterId, tSupporter *supporter, tError *retVal){
	*retVal = ERR_NOT_FOUND;	
	int n = 0;
	while (n < tabSupporters.nSupporters && *retVal == ERR_NOT_FOUND) {
		if (tabSupporters.table[n].id == supporterId) {
			supporterCpy (supporter, tabSupporters.table[n]);
			*retVal = OK;
		}
		n++;
	}	
}

/* Exercices */
/* Exercise 2.1 */
void supporterTableInit(tSupporterTable *tabSupporters) 
{
	/* Empty table, no supporters*/
	
	/*An initialized table is a table that is empty*/
	tabSupporters->nSupporters=0;
}

/* Exercise 2.2 */
void supporterTableAdd(tSupporterTable *tabSupporters, tSupporter supporter, tError *retVal) {	
	/*Add a new supporter*/
	
	/* Check if there enough space for the new supporter */
	if(tabSupporters->nSupporters >= MAX_SUPPORTERS) {
		*retVal = ERR_MEMORY;
	}
	else {
		/* Add the new supporter to the end of the table */
		supporterCpy(&tabSupporters->table[tabSupporters->nSupporters], supporter);
		tabSupporters->nSupporters++;
		*retVal = OK;
	}	
}


/* Exercise 2.3 */
float averageSpendingByEvent (tSupporter supporter, tEventType eventType) {
	float avgSpending = 0.0;
	
	int totalEventsT = 0;
	float sumSpending = 0.0;
	int i = 0;
	
	/*Calculate average spending by a supporter on a type of event*/
	for(i=0;i<supporter.tickets.nTickets;i++){
		if(supporter.tickets.table[i].eventType == eventType){
			totalEventsT=totalEventsT+1;
			sumSpending=sumSpending+supporter.tickets.table[i].price;
		}
	}
	if(totalEventsT!=0){
		avgSpending=sumSpending/(float)totalEventsT;
	}
	return avgSpending;
}
