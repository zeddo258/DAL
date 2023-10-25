//11127129�i�a�� 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

class Maze{
private:
	int mazex;             //�x�s�g�cx�b���� 
	int mazey;             //�x�s�g�cy�b���� 
	char **mazeptr = NULL; //�x�s��l�g�c�}�C 
	char **vmazeptr = NULL;//�x�s���L���g�c�}�C
	char **pmazeptr = NULL;//�x�s���\���|���g�c�}�C
	bool have = true;      //true��ܦ��g�c 
	int goals;             //�x�s�ؼмƶq 
	
public:
    
    //����ʺA�}�C�Ŷ� 
 	void Free(){
 		
    	for (int z = 0; z < mazey; z++) {
        	free(mazeptr[z]);
   		}
   		free(mazeptr);
   		
   		for (int z = 0; z < mazey; z++) {
        	free(vmazeptr[z]);
   		}
   		free(vmazeptr);
   		
   		for (int z = 0; z < mazey; z++) {
        	free(pmazeptr[z]);
   		}
   		free(pmazeptr);
   		
	}
	
    void Setv() {
    	
    	//��x�My�ӳ]�w�@�ӤG���r���}�C
    	char **maze = (char **)malloc(mazey * sizeof(char *));
    	for (int z = 0; z < mazey; z++) {
        	maze[z] = (char *)malloc(mazex+2 * sizeof(char));
   		}
   		
   		//�N�g�c�}�C�s�Jprivate���ܼ� 
   		vmazeptr=maze;
   		
   		//���l�g�c���ƾڽƻs�iV�g�c 
    	for (int i = 0; i < mazey; i++) {
        	for (int j = 0; j < mazex; j++) {
            	vmazeptr[i][j] = mazeptr[i][j];
            	vmazeptr[i][j+1]='\n';
        	}
        	
    	}
	}
	
	void Setp() {
    	
    	//��x�My�ӳ]�w�@�ӤG���r���}�C
    	char **maze = (char **)malloc(mazey * sizeof(char *));
    	for (int z = 0; z < mazey; z++) {
        	maze[z] = (char *)malloc(mazex+2 * sizeof(char));
   		}
   		
   		//�N�g�c�}�C�s�Jprivate���ܼ�
   		pmazeptr=maze;
   		
   		//���l�g�c���ƾڽƻs�iR�g�c
    	for (int i = 0; i < mazey; i++) {
        	for (int j = 0; j < mazex; j++) {
            	pmazeptr[i][j] = mazeptr[i][j];
            	pmazeptr[i][j+1]='\n';
        	}
        	
    	}
	}
	
    void SetMaze(FILE *file) {
        char buffer[1000];//�x�s�ɮרC�檺���e
    	char all[1000];   //�x�s�ɮץ��������e 
		char temp;        //�Ȧs�r�� 
		char xc[10]="";   //�x�s�}�Cx�b���ת��r�� 
		char yc[10]="";   //�x�s�}�Cy�b���ת��r��  
		int x;            //�x�s�}�Cx�b���� 
		int y;            //�x�s�}�Cy�b���� 
		int i=3;          //����ɮת��r��q��4�Ӷ}�l�����Ħr���]���]��3
		
		//Ū���C�檺���e����S�� 
		while(fgets(buffer, sizeof(buffer), file) != NULL) {
    		// �b�o�̳B�zŪ�������e
			//�NŪ�쪺���e�걵��all 
    		strcat(all,buffer);
		}
		
		//�qall��Ū�Xx������ 
		temp=all[i];
		//Ū�Ĥ@�ӪŮ�e���Ҧ��r�� 
		int a =0;
		while(temp!=' '){
			
			xc[a]=temp;
			xc[a+1]='\0';	
			
			a++;
			i++;
			temp=all[i];	
		}
		//�N�r����Ʀr 
		x = atoi(xc);
		
		//�qall��Ū�Xy������
		i++;
		temp=all[i];
		//Ū�Ĥ@�Ӵ���e���Ҧ��r��
		a=0;
		while(temp!='\n'){			
			yc[a]=temp;
			yc[a+1]='\0';
			a++;
			i++;
			temp=all[i];	
		}
		//�N�r����Ʀr
		y = atoi(yc);
		
		//�Y�O��b���@�b��0�Ahave=false
		if(x<=0||y<=0){
			have=false;
		}
			
		//��x�My�ӳ]�w�@�ӤG���r���}�C 
		char **maze = (char **)malloc(y * sizeof(char *));
    	for (int z = 0; z < y; z++) {
        	maze[z] = (char *)malloc(x+2 * sizeof(char));
   		}
   		
   		//�N�g�c����T�̧�Ū�J�}�C 
   		int j=0,k=0;
   		while(j<y){
   			i++;
			temp=all[i];
			k=0;
			while(temp!='\n'&&temp!='\0'){ 
				maze[j][k]=temp;
				i++;
				temp=all[i];
				k++;	
			}	
			j++;
	    }
   		
   		//�N�g�c�}�C�M���e�s�Jprivate���ܼ� 
   		mazex=x;
   		mazey=y;
   		mazeptr=maze; 
   		maze=NULL;
   		
   		Setv(); //�I�sSetv()�]�wV�}�C 
   		Setp(); //�I�sSetp()�]�wR�}�C 
   		
    }

    //�ΨӨ��o��l�g�c���禡 
    char ** GetMaze() {
     	return mazeptr;
    }
    
    //�ΨӨ��oV�g�c���禡
    char ** GetvMaze() {
     	return vmazeptr;
    }
    
    //�ΨӨ��oR�g�c���禡
    char ** GetpMaze() {
     	return pmazeptr;
    }
    
    //�ΨӨ��o�g�cx�b���禡
    int Getx(){
    	return mazex;
	}
	
	//�ΨӨ��o�g�cy�b���禡
	int Gety(){
    	return mazey;
	}
	
	//�Ψӳ]�whave���禡
	void Sethave(bool x){
    	have=x;
	}
    
    //�ΨӨ��ohave���禡
    bool Gethave(){
    	return have;
	}
	
	//�Ψӳ]�wgoals���禡
	void Setgoals(int x){
		goals=x;
	}
    
    bool OneGo(int x, int y,int direction) {
		// �w�q��V�]�k�U���W�^
		int dx[] = {0, 1, 0, -1};
		int dy[] = {1, 0, -1, 0};
		
    	// �p�G�ثe��m�O�ؼСA��^true
    	if (mazeptr[x][y]=='G') {
        	return true;
    	}
		
   		// �]�w�ثe��m���w���L 
    	vmazeptr[x][y] = 'V';
		
		//�~����եثe����V 
		if(direction >=0 &&direction <=3){
			//�Nx,y�H�ثe��V���e�@�� 
			int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// �ˬd�s��m�O�_�b�g�c�d�򤺡A�B�O�@�ӥ��X�ݹL�B�ਫ�����I
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V') {
            	// ���j�j���s��m
            	if (OneGo(newx, newy,direction)) {
           	     	// �p�G���@���q���X�f�����|�A��^true
           	     	// �ñN�����|�bR�}�C�ФWR 
           		   	pmazeptr[x][y] = 'R';
            	   	return true;
         		}
       	 	}
       	 	//�Y����V������ؼЫh�N��V��V�U�@�Ӥ�V 
       	 	direction=direction+1;
			
		}
		
    	// ���ճѾl�T�ӥi�઺��V
    	for (int i = 0; i < 3; i++) {
    		//��V>3�N�N��V�k�s 
    		if(direction>3){
    			direction=0;
			}
			//�Nx,y�H�ثe��V���e�@�� 
        	int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// �ˬd�s��m�O�_�b�g�c�d�򤺡A�B�O�@�ӥ��X�ݹL�B�ਫ���I
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V') {
            	// ���j�j���s��m
            	if (OneGo(newx, newy,direction)) {
           	   		// �p�G���@���q���X�f�����|�A��^true
           	   		// �ñN�����|�bR�}�C�ФWR 
           	     	pmazeptr[x][y] = 'R';
                	return true;
         		}
       	 	}
       	 	//�Y����V������ؼЫh�N��V��V�U�@�Ӥ�V
       	 	direction=direction+1;
    	}

		
    	// �p�G�Ҧ���V���L�k�����|�A��^false
    	return false;
	}
	
	bool MoreGo(int x, int y,int direction) {
		// �w�q��V�]�k�U���W�^
		int dx[] = {0, 1, 0, -1};
		int dy[] = {1, 0, -1, 0};
		
		//�Y�O�ؼФw�g�䧹�A��^true 
		if(goals==0){
    		return true;
		}
    	
		
   		// �]�w�ثe��m(����OG)���w���L
		if(vmazeptr[x][y]!='G'){
			vmazeptr[x][y] = 'V';
		} 
    	
    	//�~����եثe����V
    	if(direction >=0 &&direction <=3){
    		//�Nx,y�H�ثe��V���e�@��
			int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// �ˬd�s��m�O�_�b�g�c�d�򤺡A�B�O�@�ӥ��X�ݹL�B�ਫ�S����O�w���L���ؼЪ��I
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V'&&
				mazeptr[newx][newy] != 'T') {
				
				//�Y����ؼЫh�N�ؼг]��T(TAKE)�A�B goals-1
				if (mazeptr[newx][newy]=='G') {
    				mazeptr[newx][newy]='T';
    				goals=goals-1;
    			}
            	// ���j�j���s��m
            	if (MoreGo(newx, newy,direction)) {
                	// �p�G���@�����|�A��^true
                	// �ñN�����|(�ؼЦ�m����)�bR�}�C�ФWR 
                	if(mazeptr[x][y] != 'T'&&mazeptr[x][y] != 'G'){
                		pmazeptr[x][y] = 'R';
					}
					
					return true;
         		}
         		//�Ngoals!=0�������ؼи��|(�ؼЦ�m����)�bR�}�C�ФWR 
         		else if(pmazeptr[newx][newy]=='G'||pmazeptr[newx][newy]=='R'&&
				        pmazeptr[x][y]!='G'){
         			pmazeptr[x][y] = 'R';
				}
       	 	}
       	 	//�Y����V������ؼЫh�N��V��V�U�@�Ӥ�V
       	 	direction=direction+1;	
			
		}
		
    	// ���ճѾl�T�ӥi�઺��V
    	for (int i = 0; i < 3; i++) {
    		//��V>3�N�N��V�k�s
    		if(direction>3){
    			direction=0;
			}
			//�Nx,y�H�ثe��V���e�@��
        	int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// �ˬd�s��m�O�_�b�g�c�d�򤺡A�B�O�@�ӥ��X�ݹL�B�ਫ�S����O�w���L���ؼЪ��I
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V'&&
				mazeptr[newx][newy] != 'T') {
            		
            	//�Y����ؼЫh�N�ؼг]��T(TAKE)�A�B goals-1
            	if (mazeptr[newx][newy]=='G') {
    				mazeptr[newx][newy]='T';
    				goals=goals-1;
    			}
    			
            	// ���j�j���s��m
            	if (MoreGo(newx, newy,direction)) {
                	// �p�G���@�����|�A��^true
                	// �ñN�����|(�ؼЦ�m����)�bR�}�C�ФWR 
                	if(mazeptr[x][y] != 'T'&&mazeptr[x][y] != 'G'){
                		pmazeptr[x][y] = 'R';
					}
					
					return true;
         		}
         		//�Ngoals!=0�������ؼи��|(�ؼЦ�m����)�bR�}�C�ФWR
         		else if(pmazeptr[newx][newy]=='G'||pmazeptr[newx][newy]=='R'&&
				        pmazeptr[x][y]!='G'){
         			pmazeptr[x][y] = 'R';
				}
       	 	}
       	 	//�Y����V������ؼЫh�N��V��V�U�@�Ӥ�V
       	 	direction=direction+1;
    	}
		
    	// �p�G�Ҧ���V���L�k�����|�A��^false
    	return false;
	}
};

Maze Set(Maze maze){
	char num[100] ;         //�s�ϥΪ̿�J���ɮ׸��X 
	char fname[200]="input";//�s����ɮת��W�r 
	char trash;             //�s���ݭn������ 
	
	//Ū�J�ɮ׸��X 
	printf("Input a file number:");
	scanf("%s",&num); 
	
	//�걵�ɦW 
	strcat(fname,num);
	strcat(fname,".txt");
	
	//�}�Ҭ������ 
	FILE *file;
	file = fopen(fname, "rb"); // �H��Ū�Ҧ����}���
	if (file == NULL) {
		//�䤣�즹���h��X���~�T�� 
    	printf("\ninput%s.txt does not exist!\n",num);
    	//�ñNmaze����have�]��false
    	maze.Sethave(false);
	}
	else{
		//���h�I�smaze.SetMaze()�~�����g�c�]�w 
		maze.SetMaze(file);
		//�]�w����������� 
		fclose(file);
	}
	
	
	//Ū���e��Ū���ɮ׸��X�T���h�l������
	scanf("%c",&trash);
	printf("\n");
	return maze; //�N�]�w�n��class�^�� 
}

void One(){
	Maze maze;          // �إߤ@�ӷs��Maze class 
	char **pmaze = NULL;// �s��R�����G�}�C 
	char **vmaze = NULL;// �s��V�����G�}�C 
	
	//�I�sSet()�i��g�c�]�w 
	maze=Set(maze);
	
	// ��maze.Gethave()�ˬd�T�꦳�g�c 
	if (maze.Gethave()){
	
		//�Y�����ؼЫh��XV�}�C�MR�}�C
		//(0,0,0)�N��q�y��(0,0)�}�l��V�¥k 
		if (maze.OneGo(0,0,0)) {
		
			vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);	
				}
				printf("\n");
    	    }
    	    printf("\n");
			pmaze=maze.GetpMaze();
    	    for (int i = 0; i < maze.Gety(); i++) {
    	    	for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",pmaze[i][j]);
				}
				printf("\n");   
    	    }
    	    printf("\n");
    	} 
    	//�Y�S���ؼЫh�u��XV�}�C
		else {
    	    vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
    	}
	}
	maze.Free();
}

void More(){
	Maze maze;          // �إߤ@�ӷs��Maze class 
	int goals;          // �sŪ�J���ؼм� 
	char trash;         // �s���ݭn������
	char **pmaze = NULL;// �s��R�����G�}�C
	char **vmaze = NULL;// �s��V�����G�}�C
	
	//�I�sSet()�i��g�c�]�w 
	maze=Set(maze);
	
	// ��maze.Gethave()�ˬd�T�꦳�g�c
	if(maze.Gethave()){
	
		//�߰ݨ�Ū�J�ؼм� 
		printf("Number of G (goals):");
		scanf("%d",&goals);
		printf("\n");
		while(goals<1||goals>100){
			printf("### The number must be in [1,100] ###\n\n");
			printf("Number of G (goals):");
			scanf("%d",&goals);
			printf("\n");
		}
		//�I�sSetgoals()�]�w�ؼм� 
		maze.Setgoals(goals);
	
		//�Y�������D�ƶq���ؼЫh��XV�}�C�MR�}�C
		//(0,0,0)�N��q�y��(0,0)�}�l��V�¥k 
		if (maze.MoreGo(0,0,0)) {
		
			vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
			pmaze=maze.GetpMaze();
    	    for (int i = 0; i < maze.Gety(); i++) {
    	    	for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",pmaze[i][j]);
				}
				printf("\n");   
    	    }
    	    printf("\n");
    	} 
		//�Y�S���ؼЫh�u��XV�}�C
		else {
    	    vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
    	}
	
		//Ū���ؼмƫ᭱������ 
		scanf("%c",&trash);
	}
	maze.Free();
}



int main(int argc, char** argv) {
	char trash;      //�s���ݭn������
	char dowhat='\0';//�s�����O
	
	//�����a�߰ݭn���檺�ʧ@�����J0�h�X 
	while(dowhat!='0'){
		//�L�X������Ū�����O 
		printf("*** Path Finding ***\n");
    	printf("* 0. Quit          *\n");
    	printf("* 1. One goal      *\n");
    	printf("* 2. More goals    *\n");
    	printf("********************\n");
    	printf("Input a command(0, 1, 2):");
		scanf("%c",&dowhat);
		printf("\n");
	
	    //�Y�D�X�k���O�h��X���~�T���A�X�k�h��������ʧ@ 
		if(dowhat!='0'&&dowhat!='1'&&dowhat!='2'){
			printf("Command does not exist!\n");
			//Ū���e�����O�T���h�l������ 
			if(dowhat!='\n'){
				scanf("%c",&trash);	
			}
			
			printf("\n");
		}
		else if(dowhat=='1'){
			//���O��1�h�I�sOne()�������{�� 
			One();
		}
		else if(dowhat=='2'){
			//���O��1�h�I�sMore()�������{��
			More();
		}
		
	}
	

}
