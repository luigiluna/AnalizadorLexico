#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam 100
typedef struct tabela{
 char token[tam];
 struct tabela *prox;
}table;

char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
'r', 's', 't', 'u', 'v', 'x', 'y', 'z','0','1','2','3','4','5','6','7','8','9','=','<','<','(',')','{','}','+','-','%',',',';','"','[',']','/',':','\0'};

char caracterInvalido;
int linha = 0;
void inserirTable(table **topo, char s[]);
void lerTable(table **topo);
void imprimirTable(table *topo);
int compAlfabeto(char aux[]);
int compTable(table *topo, char aux[]);
void validarLinguagem(table **topo);


int main()
{
  table *topo=NULL;
  lerTable(&topo);
  validarLinguagem(&topo);

}

void inserirTable(table **topo, char s[]){
	table *novo;
	novo = (table*)malloc(sizeof(table));
    strcpy(novo->token,s);
    if(*topo == NULL){
        novo->prox=NULL;
        *topo = novo;
    }
    else {
        novo->prox = *topo;
        *topo = novo;
    }


}

void lerTable(table **topo){
    FILE *file;
    char aux[tam];

    file = fopen("table.txt","r");
    while(fscanf(file," %[^\n]s",&aux)!=EOF){
        inserirTable(&(*topo),aux);
    }
}

void imprimirTable(table *topo){
    system("cls");
    if(topo == NULL){
        printf("Tabela vazia\n");
    }
    else {
        while(topo != NULL){
            printf("%s\n", topo->token);
            topo = topo->prox;
        }
    }

    system("pause");
}

int compTable(table *topo, char aux[]){
    if(topo == NULL){
        printf("Tabela vazia\n");
    }
    else {
        while(topo != NULL){
            if(strcmp(aux,topo->token)==0){
                return 1;
            }
            topo = topo->prox;
        }
    }
    return 0;

}

int compAlfabeto(char aux[]){
    int i,j,control=0;
    for(i=0; aux[i]!='\0';i++){
        for(j=0; alfabeto[j]!='\0';j++){
            if(aux[i]==alfabeto[j]){
                control = 1;
            }
        }
        if(control!=1){
            caracterInvalido = aux[i];
            return 0;
        }
        control  = 0;
    }
    return 1;

}
void validarLinguagem(table **topo){
    FILE *file,*valid;
    char aux[tam],var[tam],control,*tok,*tok2,*tok3,arquivo[tam];
    int auxvalid=0,linha=1;
    system("cls");
	printf("Digite o nome e extensao do arquivo contendo a linguagem a ser analisada, ex: linguagem.txt: ");
	gets(arquivo);
	file = fopen(arquivo,"r");
	if(file==NULL){
		printf("Arquivo inexistente\n");
		system("pause");
		validarLinguagem(&(*topo));
	} 
	else {
	    valid = fopen("validacao.txt","w");
	    while(fscanf(file," %[^\n]s", &aux)!=EOF){
	        if(!memcmp(aux,"num ",4)){
	            tok = &aux;
	            tok2 = &aux;
	            while(*tok!='\0'){
	                if(*tok==','||*tok==' '){
	                    *tok='\0';
	                }
	                tok++;
	            }
	                tok3 = tok;
	                tok = &aux;
	            while(tok != tok3){
	                if(*tok=='\0'){
	                   if(*tok2!='\0'){
	                       if(compAlfabeto(tok2)){
	                           inserirTable(&(*topo),tok2);
	                       }
	                       else{
	                            fprintf(valid,"Na linha %d o caracter '%c' na palavra '%s' e invalido\n", linha,caracterInvalido, tok2);
	                            auxvalid = 1;
	                       }
	                   }
	                   tok++;
	                   tok2=tok;
	                } else{
	                    tok++;
	                }
	            }
	            if(*tok2!='\0'){
	                if(compAlfabeto(tok2)){
	                        inserirTable(&(*topo),tok2);
	                }
	                else{
	                    fprintf(valid,"Na linha %d o caracter '%c' na palavra '%s' e invalido\n", linha,caracterInvalido, tok2);
	                    auxvalid = 1;
	                }
	            }
	
	        }
	        else{
	            tok = &aux;
	            while(*tok!='\0'){
	                if(*tok=='('||*tok==')'||*tok=='{'||*tok=='}'||*tok=='='||*tok=='>'||*tok=='<'||*tok=='+'||*tok=='-'||*tok=='*'||*tok=='/'||*tok=='%'||*tok==':='||*tok==' '||*tok=='"'){
	                   if(*tok=='"'){
	                     do{
	                       *tok='\0';
	                        tok++;
	                     }while(*tok!='"'&&*tok!='\0');
	                     if(*tok=='\0'){
	                        fprintf(valid, "Na linha %d nao houve fechamento de \"\n",linha);
	                        auxvalid=1;
	                     }
	                     else if(*tok=='"'){
	                        *tok='\0';
	                     }
	                     }
	                   else{
	                    *tok='\0';
	                   }
	
	                }
	                    tok++;
	            }
	            tok3 = tok;
	            tok = &aux;
	            tok2 = &aux;
	            while(tok != tok3){
	                if(*tok=='\0'){
	                   if(*tok2!='\0'){
	                       if(!compTable(*topo,tok2)){
	                           fprintf(valid,"Na linha %d a seguinte palavra '%s' não foi reconhecida\n", linha,tok2);
	                           auxvalid = 1;
	                       }
	                   }
	                   tok++;
	                   tok2=tok;
	                } else{
	                    tok++;
	                }
	            }
	            if(*tok2!='\0'&&compAlfabeto(tok2)){
	                if(!compTable(*topo,tok2)){
	                    fprintf(valid,"Na linha %d a seguinte palavra '%s' não foi reconhecida\n", linha,tok2);
	                    auxvalid = 1;
	                }
	            }
	            }
	            linha++;
	    }
	    if(!auxvalid){
	        fprintf(valid,"A linguagem e valida!");
	    }
	    fclose(valid);
	}
}








