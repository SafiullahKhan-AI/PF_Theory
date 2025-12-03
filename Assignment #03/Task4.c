#include <stdio.h>
#include <string.h>

struct Book{
    int id;
    int popularity;
    int lastAccess;
};

int main(){
    int cpcty, Q;
    scanf("%d %d", &cpcty, &Q);

    struct Book shelf[cpcty];
    int counter = 0;
    int timeStamp = 1;

    for(int i = 0; i < cpcty; i++){
        shelf[i].id = -1;
    }

    while(Q--){
        char op[10];
        scanf("%s", op);

        if(strcmp(op, "ADD") == 0){
            int x, y;
            scanf("%d %d", &x, &y);

            int found = -1;

            for(int i = 0; i < cpcty; i++){
                if(shelf[i].id == x){
                    found = i;
                    break;
                }
            }

            if(found != -1){

                shelf[found].popularity = y;
                shelf[found].lastAccess = timeStamp++;
            } 
            else{
                if(counter < cpcty){
                    shelf[counter].id = x;
                    shelf[counter].popularity = y;
                    shelf[counter].lastAccess = timeStamp++;
                    counter++;
                } 
                else{
                
                    int lruIndex = 0;

                    for(int i = 1; i < cpcty; i++){
                        if(shelf[i].lastAccess < shelf[lruIndex].lastAccess){
                            lruIndex = i;
                        }
                    }

                    shelf[lruIndex].id = x;
                    shelf[lruIndex].popularity = y;
                    shelf[lruIndex].lastAccess = timeStamp++;
                }
            }
        }

        else if(strcmp(op, "ACCESS") == 0){
            int x;
            scanf("%d", &x);
            int found = -1;

            for(int i = 0; i < cpcty; i++){
                if (shelf[i].id == x){
                    found = i;
                    break;
                }
            }

            if(found == -1){
                printf("-1\n");
            } 
            else{
                shelf[found].lastAccess = timeStamp++;
                printf("%d\n", shelf[found].popularity);
            }
        }
    }

    return 0;
}
