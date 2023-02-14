#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>


int	main(int argc, char **argv)
{
	int i = 0;
	char	*input;

	if(access("okunamaz.txt", R_OK) == 0)
		printf("okunamaz.txt dosyasi okunabilir\n");
	else
		printf("okunamaz.txt dosyasi okunamaz\n");
	while (1)
	{
		input = readline("prompt> ");		//-> readline ile input almak
		if (!input)
			break ;
		add_history(input); 		//-> history ekleme
		printf("You entered: %s\n", input);
		replace_history_entry(i, "degisti", NULL);	//-> history degistirme
		rl_redisplay();
		//clear_history(); 		//-> history silmek icin
		//rl_on_new_line();		//-> yeni satira gecmek icin ?????
		free(input);
		i++;
	}
	return (0);
}
