
extern num_lines;
extern num_chars;
extern state_chg[];
extern i;


int main(void)
{
        int i;

        for(i=0; i<3; ++i) {
          state_chg[i]=0;
         }

	yylex();
        printf("\nFinal Status:\n"
               "  state_chg[0]=%d\n"
               "  state_chg[1]=%d\n"
               "  state_chg[2]=%d\n",
                  state_chg[0],state_chg[1],state_chg[2]);

        return 0;
}
