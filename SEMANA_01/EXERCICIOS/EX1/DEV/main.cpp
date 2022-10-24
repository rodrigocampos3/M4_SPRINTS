#include <iostream>
#include <string>
using namespace std;

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor

int converteSensor(int Vminimo, int Vmaximo, int Vdistancia){
	float calc1 = Vdistancia - Vminimo;
	float calc2 = Vmaximo - Vminimo;
	int resultado = (calc1/calc2)*100;
	return calc2;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor
int readSensor(void){
	int valor = 0; //Declaro e inicio a variavel
	cout << "Digite um valor: " << endl;
	cin >> valor;
	return valor;
}

// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor
int inserirArray(int val, int ultimo, int *i, int tamanho)
{
	int *lista = i;
	lista[ultimo] = val;
	return (ultimo + 1);
}



// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.
 const char *caminhoCurto(int *i, int *d)
{
	const char *dir[] = {"Direita", "Esquerda", "Frente", "Tras"};
	int p = 0;

	for (int o = 0; o < 4; o++)
	{
		if (i[o] > *d)
		{
			*d = i[o];
			p = o;
		}
	}
	return dir[p];
}




// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso
bool leComando(){
	char resposta ;
	cout << "Deseja continuar? [S/N]" << endl;
	cin >> resposta;
	if (resposta == 's' || resposta == 'S'){
		return true;
	}
	else {
		return false;
	}
}


// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas
int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
		int medida = readSensor();/// .. Chame a função de de leitura da medida para a "Direita"
		medida = converteSensor(medida,0,830);
		posAtualVetor = inserirArray(medida, posAtualVetor, v, maxVetor );// Chame a função para armazenar a medida no vetor
        ///////////////////////////////////////////////////////////////////////////		
		medida = readSensor();
		int vMin = readSensor();
		int vMax = readSensor();
		int vDis = readSensor();
		medida = converteSensor(vMin, vMax, vDis);
		posAtualVetor = inserirArray( medida, posAtualVetor, v, maxVetor );

		// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
		// ................
		///////////////////////////////////////////////////////////////////////////
		dirigindo = leComando();		
	}
	return posAtualVetor;
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		const char *direcao = caminhoCurto(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}