#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>

struct open
{
	int x;
	int y;
	int Parrent_x;
	int Parrent_y;
	int f_cost;
	struct open* next;
}*head_open;

struct close
{
	int x;
	int y;
	int Parrent_x;
	int Parrent_y;
	int f_cost;
	struct close* next,*prev;
}*head_close;

struct path
{
	int x;
	int y;
	struct path* next;
}*head_path,*head_grass;

void insertPath(int x,int y)
{
	struct path *new_data = (struct path*)malloc(sizeof(struct path));
	new_data->x = x;
	new_data->y = y;
	new_data->next = NULL;

	if(!head_path)
	{
		head_path = new_data;
		return;
	}
	else
	{
		struct path *tmp = head_path;
		new_data->next = tmp;
		head_path = new_data;
		return;
	}
}

void popPath()
{
	if(!head_path)
	{
		return;
	}
	if(head_path->next == NULL)
	{
		head_path = NULL;
		return;
	}
	else
	{
		struct path* tmp = head_path;
		head_path = head_path->next;
		free(tmp);
		return;
	}
}

void insertGrass(int x,int y)
{
	struct path *new_data = (struct path*)malloc(sizeof(struct path));
	new_data->x = x;
	new_data->y = y;
	new_data->next = NULL;

	if(!head_grass)
	{
		head_grass = new_data;
		return;
	}
	else
	{
		struct path *tmp = head_grass;
		new_data->next = tmp;
		head_grass = new_data;
		return;
	}
}

void popGrass()
{
	if(!head_grass)
	{
		return;
	}
	if(head_grass->next == NULL)
	{
		head_grass = NULL;
		return;
	}
	else
	{
		struct path* tmp = head_grass;
		head_grass = head_grass->next;
		free(tmp);
		return;
	}
}

void findPath(int x,int y)
{
	struct close* tmp = head_close;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	insertPath(tmp->x,tmp->y);
	int tmp_x = tmp->Parrent_x;
	int tmp_y = tmp->Parrent_y;
	while(tmp->prev != NULL)
	{
		if(tmp->x == x and tmp->y == y)
		{
			break;
		}
		if(tmp->x == tmp_x and tmp->y == tmp_y)
		{
			insertPath(tmp_x,tmp_y);
			tmp_x = tmp->Parrent_x;
			tmp_y = tmp->Parrent_y;	
		}
		tmp = tmp->prev;
	}
}

int countDistance(int x1,int x2,int y1,int y2)
{
	//manhatan distance formula
	//|x1 - x2| + |y1 - y2|
	//return (abs(x1-x2)) + (abs(y1-y2));
	return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

int countFCost(int g_cost,int h_cost)
{
	return g_cost+h_cost;
}

void find_smallest(int *coor)
{
	if(!head_open)
	{
		return;
	}

	coor[0] = head_open->x;
	coor[1] = head_open->y;
	coor[2] = head_open->f_cost;
	coor[3] = head_open->Parrent_x;
	coor[4] = head_open->Parrent_y;
	struct open *tmp = head_open;
	while(tmp->next != NULL)
	{
		if(tmp->f_cost < coor[2])
		{
			coor[0] = tmp->x;
			coor[1] = tmp->y;
			coor[2] = tmp->f_cost;
			coor[3] = tmp->Parrent_x;
			coor[4] = tmp->Parrent_y;
		}
		tmp = tmp->next;
	}
}

int insert_open(int x,int y,int Parrent_x,int Parrent_y,int f_cost)
{
	struct open *new_data = (struct open*)malloc(sizeof(struct open));
	new_data->x = x;
	new_data->y = y;
	new_data->Parrent_x = Parrent_x;
	new_data->Parrent_y = Parrent_y;
	new_data->f_cost = f_cost;
	new_data->next = NULL;

	if(!head_open)
	{
		head_open = new_data;
		return 1;
	}
	else
	{
		if(head_open->x == x and head_open->y == y)
		{
			return 0;
		}
		struct open *tmp = head_open;
		while(tmp->next != NULL)
		{
			if(tmp->x == x and tmp->y == y)
			{
				return 0;
			}
			tmp = tmp->next;
		}
		tmp->next = new_data;
		return 1;
	}
}

int insert_close(int x,int y,int Parrent_x,int Parrent_y,int f_cost)
{
	struct close *new_data = (struct close*)malloc(sizeof(struct close));
	new_data->x = x;
	new_data->y = y;
	new_data->Parrent_x = Parrent_x;
	new_data->Parrent_y = Parrent_y;
	new_data->f_cost = f_cost;
	new_data->next = NULL;
	new_data->prev = NULL;

	if(!head_close)
	{
		head_close = new_data;
		return 1;
	}
	else
	{
		if(head_close->x == x and head_close->y == y)
		{
			return 0;
		}
		struct close *tmp = head_close;
		while(tmp->next != NULL)
		{
			if(head_close->x == x and head_close->y == y)
			{
				return 0;
			}
			tmp = tmp->next;
		}
		new_data->prev = tmp;
		tmp->next = new_data;
		return 1;
	}
}

void pop_open(int x,int y)
{
	if(!head_open)
	{
		return;
	}
	if(head_open->x == x and head_open->y == y and head_open->next == NULL)
	{
		head_open = NULL;
		return;
	}
	else if(head_open->x == x and head_open->y == y)
	{
		struct open* tmp = head_open;
		head_open = head_open->next;
		free(tmp);
		return;
	}
	struct open* tmp = head_open;
	while(tmp != NULL)
	{
		if(tmp->next == NULL)
		{
			return;
		}
		if(tmp->next->x == x and tmp->next->y == y)
		{
			struct open* tmp2 = tmp->next;
			if(tmp->next->next == NULL)
			{
				tmp->next = NULL;
				free(tmp2);
				return;
			}
			tmp->next = tmp->next->next;
			free(tmp2);
			return;
		}
		tmp = tmp->next;
	}
	return;
}

void pop_close(int x,int y)
{
	if(!head_close)
	{
		return;
	}
	if(head_close->x == x and head_close->y == y and head_close->next == NULL)
	{
		head_close = NULL;
		return;
	}
	else if(head_close->x == x and head_close->y == y)
	{
		struct close* tmp = head_close;
		head_close = head_close->next;
		free(tmp);
		return;
	}
	struct close* tmp = head_close;
	while(tmp != NULL)
	{
		if(tmp->next == NULL)
		{
			return;
		}
		if(tmp->next->x == x and tmp->next->y == y)
		{
			struct close* tmp2 = tmp->next;
			if(tmp->next->next == NULL)
			{
				tmp->next = NULL;
				free(tmp2);
				return;
			}
			tmp->next = tmp->next->next;
			free(tmp2);
			return;
		}
		tmp = tmp->next;
	}
	return;
}

int search_open(int x,int y,int f_cost)
{
	if(!head_open)
	{
		return 0;
	}
	struct open *tmp = head_open;
	if(x == tmp->x and tmp->y == y and tmp->f_cost <= f_cost)
	{
		return 1;
	}
	while(tmp->next != NULL)
	{
		//printf("%i-%i(%i)////\n", tmp->x,tmp->y,tmp->f_cost);
		if(x == tmp->x and tmp->y == y and tmp->f_cost <= f_cost)
		{
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

int search_close(int x,int y,int f_cost)
{
	if(!head_close)
	{
		return 0;
	}
	struct close *tmp = head_close;
	if(x == tmp->x and tmp->y == y and tmp->f_cost <= f_cost)
	{
		return 1;
	}
	while(tmp->next != NULL)
	{
		//printf("%i-%i(%i)////\n", tmp->x,tmp->y,tmp->f_cost);
		if(x == tmp->x and tmp->y == y and tmp->f_cost <= f_cost)
		{
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

void print_open() 
{
	struct open* tmp = head_open;
	while(tmp != NULL)
	{
		printf("%i-%i(%i)\n", tmp->x,tmp->y,tmp->f_cost);
		tmp = tmp->next;
	}
}

void print_close()
{
	struct close* tmp = head_close;
	while(tmp != NULL)
	{
		printf("%i-%i->%i-%i(%i)\n",tmp->Parrent_x,tmp->Parrent_y,tmp->x,tmp->y,tmp->f_cost);
		tmp = tmp->next;
	}
}

void print_path()
{
	struct path* tmp = head_path;
	while(tmp != NULL)
	{
		printf("%i-%i\n",tmp->x,tmp->y);
		tmp = tmp->next;
	}
}

void print_grass()
{
	struct path* tmp = head_grass;
	while(tmp != NULL)
	{
		printf("%i-%i\n",tmp->x,tmp->y);
		tmp = tmp->next;
	}
}

int main()
{
	char test[21][41] = {{"----------------------------------------"},
						{"|   #   v        #                 #   |"},
						{"|   #            #                 #   |"},
						{"|   #                    ############# |"},
						{"|   ##########   #          #       #  |"},
						{"|       G  #  ####          #       #  |"},
						{"|          #     #          #          |"},
						{"|          #     #          # ######   |"},
						{"|          #### #####       #          |"},
						{"|      #                               |"},
						{"|   ####         #    #    ############|"},
						{"|   #  #         #    #         #      |"},
						{"|   #  #         #    #  ###### #      |"},
						{"|   #  #############  #         #      |"},
						{"|   #  #   #          #         #      |"},
						{"| ###  #   #                    #      |"},
						{"|      #   ##################   #      |"},
						{"|      #   #                    ###### |"},
						{"|      #                  #            |"},
						{"----------------------------------------"}};

	int grass_x = 1;
	int grass_y = 8;
	int goat_x = 5;
	int goat_y = 8;
	int Unreachable = 0;
	int coor[5];
	//A* Start here
	//Add Starting Node To The Current List
	insert_open(goat_x,goat_y,goat_x,goat_y,countFCost(0,countDistance(goat_x,grass_x,goat_y,grass_y)));
	while(1)
	{
		//If Goal Id Unreachable Or Not Exist, Stop The Search
		if(!head_open)
		{
			Unreachable = 1;
			break;
		}
		//Get The Smallest Node On Open List And Set It As The Current Node
		find_smallest(coor);
		//Remove The Current Node From Open List And Insert It To The Close List
		pop_open(coor[0],coor[1]);
		insert_close(coor[0],coor[1],coor[3],coor[4],coor[2]);
		//If The Current Node Is Our Goal, We Can Stop The Search
		if(test[coor[0]][coor[1]] == 'v')
		{
			break;
		}
		//Get Heuristic Cost Of All Of The Current Node Successor
		int cost1 = countFCost(countDistance(coor[0]+1,goat_x,coor[1],goat_y),countDistance(coor[0]+1,grass_x,coor[1],grass_y));
		int cost2 = countFCost(countDistance(coor[0]-1,goat_x,coor[1],goat_y),countDistance(coor[0]-1,grass_x,coor[1],grass_y));
		int cost3 = countFCost(countDistance(coor[0],goat_x,coor[1]+1,goat_y),countDistance(coor[0],grass_x,coor[1]+1,grass_y));
		int cost4 = countFCost(countDistance(coor[0],goat_x,coor[1]-1,goat_y),countDistance(coor[0],grass_x,coor[1]-1,grass_y));
		
		//Check For Every Successor Node From The Current Node
		//Note For My Visualization I Only Make The Agent To Only Able To Move To 4 Direction(Left,Right,Up,Down)
		//If You Want The Agent To Be Able To Move On A Diagonal Direction Then Just Add Another If Statment To Check For That Node Successor
		//If We Found Our Goal The We Can Stop
		if(test[coor[0]+1][coor[1]] == 'v')
		{
			break;
		}
		//Else If The Successor Is Never Been Visited Or Has A Lower Heuristiv Cost To Visit And This Node Is Note A Wall(A Grid We Cant Visit), Add This Node To Open List
		else if(search_open(coor[0]+1,coor[1],cost1) == 0 and search_close(coor[0]+1,coor[1],cost1) == 0 and test[coor[0]+1][coor[1]] == ' ')
		{
			pop_close(coor[0]+1,coor[1]);
			insert_open(coor[0]+1,coor[1],coor[0],coor[1],cost1);
		}
		if(test[coor[0]-1][coor[1]] == 'v')
		{
			break;
		}
		else if(search_open(coor[0]-1,coor[1],cost2) == 0 and search_close(coor[0]-1,coor[1],cost2) == 0 and test[coor[0]-1][coor[1]] == ' ')
		{
			pop_close(coor[0]-1,coor[1]);
			insert_open(coor[0]-1,coor[1],coor[0],coor[1],cost2);
		}
		if(test[coor[0]][coor[1]+1] == 'v')
		{
			break;
		}
		else if(search_open(coor[0],coor[1]+1,cost3) == 0 and search_close(coor[0],coor[1]+1,cost3) == 0 and test[coor[0]][coor[1]+1] == ' ')
		{
			pop_close(coor[0],coor[1]+1);
			insert_open(coor[0],coor[1]+1,coor[0],coor[1],cost3);
		}
		if(test[coor[0]][coor[1]-1] == 'v')
		{
			break;
		}
		else if(search_open(coor[0],coor[1]-1,cost4) == 0 and search_close(coor[0],coor[1]-1,cost4) == 0 and test[coor[0]][coor[1]-1] == ' ')
		{
			pop_close(coor[0],coor[1]-1);
			insert_open(coor[0],coor[1]-1,coor[0],coor[1],cost4);
		}
		//Print The Map For Visualization
		struct close* tmp = head_close;
		while(tmp != NULL)
		{
			if(test[tmp->x][tmp->y] != 'G')
			{
				test[tmp->x][tmp->y] = '$';
			}
			tmp = tmp->next;
		}
		system("CLS");
		for(int i=0;i<=20;i++)
		{
			for(int x = 0;x<= 40;x++)
			{
				printf("%c",test[i][x]);
			}
			printf("\n");
		}
	}
	//If Goal Is Reachable Then Create The Path To Goal
	if(Unreachable == 0)
	{
		findPath(goat_x,goat_y);
		struct path* tmp = head_path;
		while(tmp != NULL)
		{
			test[tmp->x][tmp->y] = '+';
			system("CLS");
			for(int i=0;i<=20;i++)
			{
				for(int x = 0;x<= 40;x++)
				{
					printf("%c",test[i][x]);
				}
				printf("\n");
			}
			tmp = tmp->next;
		}
	}
	else
	{
		printf("DESTINATION UNREACHBLE\n");
	}
}