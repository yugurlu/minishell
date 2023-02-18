#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>


int	main(int argc, char **argv)
{
	int i = 0;
	char	*input;
	sigset_t set;
	struct stat file_info;
	pid_t pid;
	char *args[] = { "/bin/ls", "-l"};

	sigemptyset(&set);		//-> seti bosalt / oluştur
	sigaddset(&set, SIGINT); 	//-> sete SIGINT ekle
	//sigprocmask(SIG_BLOCK, &set, NULL);		//-> seti bloke et
	input = getcwd(NULL, 0);		//-> getcwd ile path almak

	stat("okunamaz.txt", &file_info);	//-> dosya bilgilerini almak
	//printf("okunamaz.txt dosyasinin sahibi: %lld\n", file_info.st_size);
	unlink("okunamaz.txt");		//-> dosya silmek
	int a = open("okunamazz.txt", O_RDWR | O_CREAT, 0777);	//-> dosya acmak
	int b = open("okunamaz2.txt", O_RDWR | O_CREAT, 0777);	//-> dosya acmak
	int c = dup(a);		//-> dosya acmak

	pid = fork();		//-> fork ile cocuk olusturmak
	if (pid == 0)
	{
		printf("cocuk\n");
		exit(0);
	}
	printf("baba\n");
	printf("%hhu\n",readdir(opendir("/Users/yusufugurlu/Desktop/minishell"))->d_type);		//-> readdir ile klasor okumak

	//execve("/bin/ls", args, NULL);		//-> execve ile ls calistirmak

	printf("%d\n\n",ttyslot());		//-> ttyname ile terminal adini almak
	if(access("okunamaz.txt", R_OK) == 0)
		printf("okunamaz.txt dosyasi okunabilir\n");
	else
	{
		printf("okunamaz.txt dosyasi okunamaz\n");
		perror(strerror(1));		//-> hata mesaji almak

	}
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
