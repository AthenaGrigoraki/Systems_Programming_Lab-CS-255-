#include "sudoku.h"

#include <string.h>
#include <ctype.h>

/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
Grid_T sudoku_read(void)
{
    Grid_T grid;
    int i = 0, j = 0; /*to i einai oi grammes*/
    char c;
    grid_clear_unique(&grid);

    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            int num = c - '0'; /*metatrepei ena char se int*/

            grid_update_value(&grid, i, j, num);
        }
        else if (c == ' ')
        {

            continue;
        }
        else if (c == '\n')
        {
            i++; /*grammi stin opoia vriskomaste*/
            j = -1; /*kate fora poy allazei grammi midenizoume to j etsi wste na arxisei na metraei stiles aptin arxi*/

        }

        j++;

    }
    printf("\n");
    return grid;
}

/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g)
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            fprintf(s, "%d ", grid_read_value(g, i, j)); /* printarei kathe timi tou puzzle*/
        }
        fprintf(s, "\n");
    }
}

/*returns flag , if 1 then error ,if 0 then right */
int same_numbers(Grid_T g)
{
    int i, j, check, n, k, l;
    int flag = 0; /*checks for error in each grid*/

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            n = grid_read_value(g, i, j); /*diavazei oles tis times tou puzzle*/
            /*checks 3x3*/
            if ((i == 0 || i == 3 || i == 6) && (j == 0 || j == 3 || j == 6)) /*tsekarei kathe 3x3 grid*/
            {
                int gridflag[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                int m;

                for (k = i; k < (i + 3); k++)
                {
                    for (l = j; l < (j + 3); l++)
                    {
                        m = grid_read_value(g, k, l);
                        if (m == 0)
                        {
                            continue;
                        }
                        if (gridflag[m - 1] == 1) /*ama to sinantisi kai einai idi ena simainei oti iparxei ksana*/
                        {
                            flag = 1;
                            fprintf(stderr, "duplicate number(%d) in same 3x3 grid(%d - %d)\n", m, k, l); /*mipos in grid i,j anti k,l*/
                        }
                        else
                        {
                            gridflag[m - 1] = 1; /*molis sinantisei ena arithmo apo 0-9 thetei to gridflag 1*/
                        }
                    }
                }
            }

            if (n == 0)
            {
                continue;
            } /*here checks for row and col */
            for (check = 0; check < 9; check++)
            {
                if (n == grid_read_value(g, check, j) && check != i)
                {
                    flag = 1;
                    fprintf(stderr, "duplicate number(%d) in same column(%d)\n", n, j);
                }
                if (n == grid_read_value(g, i, check) && check != j)
                {
                    flag = 1;
                    fprintf(stderr, "duplicate number(%d) in same row(%d)\n", n, i);
                }
            }
        }
    }

    return flag;
}

void sudoku_print_errors(Grid_T g)
{
    same_numbers(g);
}

/* Return true if puzzle g is correct. */
int sudoku_is_correct(Grid_T g)
{
    if (same_numbers(g))
    {

        return 0;
    }
    else
    {
        return 1;
    }
}

/* initializes possible choices*/
static void sudoku_init_choices(Grid_T *g)
{

    int i, j, k, l, val;
    int r, c;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            val = grid_read_value(*g, i, j);
            if (val != 0)
            {
                grid_clear_count(g, i, j); /*if not 0, we dont have choice*/

                grid_clear_choice(g, i, j, val); /*not valid choice*/
            }
            else
            {

                /*  choices[i][j] = 1 , so that when invalid choices[i][j]=0*/
                int r1;
                for (r1 = 1; r1 < 10; r1++)
                {
                    grid_set_choice(g, i, j, r1); /*an to value einai 0 exei oles tis epiloges epiloges*/
                    grid_set_count(g, i, j);
                }

                for (l = 0; l < 9; l++)
                {
                    int val2;
                    /*checks column*/
                    val2 = grid_read_value(*g, l, j);

                    if (val != val2 && l != i)
                    {
                        grid_remove_choice(g, i, j, val2); /*an iparxei stin idia stili opoiadipote timi vgazoume tin epilogi*/
                    }

                    /*checks row*/
                    val2 = grid_read_value(*g, i, l);

                    if (val != val2 && l != j)
                    {
                        grid_remove_choice(g, i, j, val2);
                    }
                }

                /*checks grid*/

                k = i - i % 3;
                l = j - j % 3;
                for (r = 0; r < 3; r++)
                {
                    for (c = 0; c < 3; c++)
                        val = grid_read_value(*g, k + r, l + c);
                    if (i != k + r && j != l + c)
                    {
                        grid_remove_choice(g, i, j, val);
                    }
                }
            }
        }
    }
}

static int sudoku_try_next(Grid_T g, int *row, int *col)
{
    int min_count = 12; /*a random number bigger than 9*/
    int i, j, k, count;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            count = grid_read_count(g, i, j); /*oles oi dinates epiloges*/

            if (count == 0) /*if number not zero*/
            {
                continue;
            }
            else if (count <= min_count ) /*find the element with the least choices at first*/
            {


                *row = i;
                *col = j;
                if( count != -1){

                min_count = count;
                }

                for (k=1; k<10; k++){
                    if(grid_choice_is_valid(g,*row,*col,k)){

                        return k;
                    }
                }


            }
            else if (min_count > 9)
            { /*if no element has count<9*/
                return 0;
            }
        }
    }


    return 0;
}

static int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
    grid_remove_choice(g, i, j, n); /*remove choice*/
    grid_update_value(g, i, j, n);  /*new value*/

    return grid_read_count(*g, i, j);
}

static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
    int k, l, i, j;

    /*fow rows and columns*/
    for (k = 0; k < 9; k++)
    {
        grid_remove_choice(g, r, k, n);
        grid_remove_choice(g, k, c, n);
    }

    /*for 3x3 grid*/

    k = r - r % 3;
    l = c - c % 3;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)

            grid_remove_choice(g, k + i, l + j, n);
    }
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g)
{
    int i = 0, j = 0;
    int k;
    Grid_T grid;

    sudoku_init_choices(&g);
    while (1)
    {
        k = sudoku_try_next(g, &i, &j);

        if (k == 0)
        {
            return g;
        }

        if (sudoku_update_choice(&g, i, j, k) != 0) /*while count is bigger 0*/
        {
            grid = sudoku_solve(g);

            if (sudoku_is_correct(grid))
            {

                if (grid_read_count(grid, i, j) == 0)
                {
                    grid_set_unique(&grid);
                }
                return grid;
            }
        }
        else
        {
            sudoku_eliminate_choice(&g, i, j, k); /*if not then eliminate*/
        }
    }
    return g;
}

static Grid_T sudoku_generate_complete(void)
{
    Grid_T grid;
   /* int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            grid_update_value(&grid, i, j, 0); make every element equal to 0

        }
    }
    grid = sudoku_solve(grid); then solve the puzzle*/

    sudoku_print(stdout, grid);
    return grid;
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. */
Grid_T sudoku_generate(int nelts)
{
    Grid_T grid;
    int k;
    int i;
    int j;
    grid = sudoku_generate_complete(); /*takes a solved puzzle*/

    for (k = 0; k < (81 - nelts); k++) /*finds how many elements should be changed to zero*/
    {
        i = rand() % 9; /*take random grids*/
        j = rand() % 9;

        while (grid_read_value(grid, i, j) == 0)
        {
            i = rand() % 9;
            j = rand() % 9;
        }



        grid_update_value(&grid, i, j, 0);
    }
    return grid;
}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g)
{
    return grid_read_unique(g);
}

int main(int argc, char **argv)
{
    Grid_T grid;

    /* case: sudoku*/
    if (argc == 1)
    {

        grid = sudoku_read();
        sudoku_print(stderr, grid);

        grid = sudoku_solve(grid);
        printf(" new grid: \n");


        if (!(sudoku_solution_is_unique(grid)))
        {
            printf("Solution is not unique!\n");
        }
        else
        {
            printf("Sudoku is unique!\n");
        }

        sudoku_print(stdout, grid);
    }

    /* case: sudoku -c*/
    if (argc == 2 && !strcmp(argv[1], "-c"))
    {
        grid = sudoku_read();
        sudoku_print(stderr, grid);
        if (!(sudoku_is_correct(grid)))
        {
            sudoku_print_errors(grid);
            fprintf(stderr, "Sudoku is not correct!\n");
        }
        else
        {
            printf("Sudoku is correct!\n");
        }
    }

    if (argc == 3 && !strcmp(argv[1], "-g"))
    {

        sudoku_generate(atoi(argv[2]));
        sudoku_print(stdout, grid);
    }

    return 0;
}

