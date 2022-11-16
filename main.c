#include <stdio.h>

char	**ft_cmd_split(char *input);

int	main(int arc, char **argv)
{
	char	command[] = "awk \'\"\'\"\'{count++} END {print count}\'\"\'\"\'";
//	char	command[] = "hola 1";
//	char	command[] = "./\"script space.sh\"";
//	char	command[] = "./\"script\\\"quote.sh\"";
//	char	command[] = "./\'\"\'\"\'script space.sh\'\"\'\"\'";
	char	**command_args;
	int		i;


	printf("\nTEST PARA EL SPLIT DE PIPEX\n\n");
	printf("###########################################################");
	printf("\nLa input es: %s\n", command);
	command_args = ft_cmd_split(command);
	i = 0;
	printf("Spliteo recibido:\n");
	while (command_args[i])
		printf("\t<%s>\n", command_args[i++]);
	printf("###########################################################");
	char commandd[] = "awk \"{count++} END {printf \\\"count: %i\\\" , count}\"";
	printf("\nLa input es: %s\n", commandd);
	command_args = ft_cmd_split(commandd);
	i = 0;
	printf("Spliteo recibido:\n");
	while (command_args[i])
		printf("\t<%s>\n", command_args[i++]);
	printf("###########################################################");
	char commanddd[] = "sed    \"s/And/But/\"";
	printf("\nLa input es: %s\n", commanddd);
	command_args = ft_cmd_split(commanddd);
	i = 0;
	printf("Spliteo recibido:\n");
	while (command_args[i])
		printf("\t<%s>\n", command_args[i++]);
	printf("###########################################################");
	char commandddd[] = "awk \"\'{count++} END {print count}\'\"";
	printf("\nLa input es: %s\n", commandddd);
	command_args = ft_cmd_split(commandddd);
	i = 0;
	printf("Spliteo recibido:\n");
	while (command_args[i])
		printf("\t<%s>\n", command_args[i++]);
	printf("###########################################################");
	char commmandddd[] = "\'sed    \"s/And/But/\"\'";
	printf("\nLa input es: %s\n", commmandddd);
	command_args = ft_cmd_split(commmandddd);
	i = 0;
	printf("Spliteo recibido:\n");
	while (command_args[i])
		printf("\t<%s>\n", command_args[i++]);
}
