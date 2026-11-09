#include <stdio.h>

int main(){
	
	int n, sym, start, trans[10][5], isFinal[10];
	int reachable[10] = {0}, group[10], newGroup[10], queue[10];
	int i, j, k, g, front=0, rear=0, changed, numGroups;
	
	printf("Enter the number of states: ");
	scanf("%d",&n);
	
	printf("Enter the number of input symbols: ");
	scanf("%d",&sym);
	
	printf("Enter the transition table: \n");
	for(i=0;i<n;i++)
		for(j=0;j<sym;j++)
			scanf("%d",&trans[i][j]);
			
	printf("Enter the final states (1 = final, 0 = non final): ");
	for(i=0;i<n;i++)
		scanf("%d",&isFinal[i]);
		
	printf("Enter the start state: ");
	scanf("%d",&start);
	
	queue[rear++] = start;
	reachable[start] = 1;
	
	while(front < rear){
		i = queue[front++];
		for(j=0;j<sym;j++){
			if(!reachable[trans[i][j]]){
				reachable[trans[i][j]] = 1;
				queue[rear++] = trans[i][j];
			}
		}
	}
	
	for(i=0;i<n;i++)
		group[i] = reachable[i] ? isFinal[i] : -1;
		
	do{
	
		changed = numGroups = 0;
		
		for(i=0;i<n;i++){
			
			newGroup[i] = -1;
			if(!reachable[i]) continue;
			
			for(j=0;j<i;j++){
				if(!reachable[j] || group[i] != group[j]) continue;
				
				for(k=0;k<sym && group[trans[i][k]] == group[trans[j][k]];k++);
				
				if(k==sym){
					newGroup[i] = newGroup[j];
					break;
				}
				
			}
			if(newGroup[i] == -1){
				newGroup[i] = numGroups++;
			}
		}
		
		for(i=0;i<n;i++){
			if(reachable[i]){
				for(j=0;j<i;j++){
					if(reachable[j]&&((group[i]== group[j])!=(newGroup[i] == newGroup[j]))){
						changed = 1;
					}
				}
			}
		}
		
		for(i=0;i<n;i++)
			group[i] = newGroup[i];
	
	}while(changed);
	
	numGroups = 0;
	for(i=0;i<n;i++){
		if(reachable[i] && group[i] >= numGroups)
			numGroups = group[i] + 1;
	}
	
	printf("\nMinimized DFA states: \n");
	printf("Total minimized states: %d\n\n",numGroups);
	
	for(g=0;g<numGroups;g++){
		int final = 0;
		
		printf("S%d = { ",g);
		
		for(i=0;i<n;i++){
			if(reachable[i] && group[i] == g){
				printf("q%d ",i);
				if(isFinal[i]) final = 1;
			}
			
		}
		printf("}%s\n",final ? " [FINAL] ": "");
	}
	
	printf("\nMinimized transition table: \nState");
	for(j=0;j<sym;j++) printf("\tsym%d",j);
	printf("\n");
	
	for(g=0;g<numGroups;g++){
		for(i=0;i<n && (!reachable[i] || group[i] != g); i++);
		
		printf("S%d",g);
		for(j=0;j<sym;j++)
			printf("\tS%d",group[trans[i][j]]);
		printf("\n");
	}
	printf("\nStart state: S%d\n",group[start]);
	
	return 0;
}
