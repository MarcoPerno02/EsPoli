#define RADIUS 5
extern int  Matrix_Coordinates;
extern char  ROWS;								
extern char  COLUMNS;	
extern int check_square(int x, int y, int r);
extern float my_division(float* a, float* b);

int main(void){

	int i, x_value, y_value, dim = ROWS * COLUMNS ;
	int * matrix = &Matrix_Coordinates;
	
	volatile float area = 0.;
	// Variabile where I will calculate pi
	volatile float pi_calculated = 0.;
	
	float radiusPower2 = (float) (RADIUS * RADIUS);
	
	for(i = 0; i < dim; i += 2) 
	{
		x_value = matrix[i];
		y_value = matrix[i + 1];

		// Call my check for pi
		area += check_square(x_value ,y_value, RADIUS);
	}	
	
	// Call my asm for division
	pi_calculated = my_division((float * ) &area,&radiusPower2);
	
	while(1);
}

