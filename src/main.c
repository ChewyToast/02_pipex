
#include "pipex.h"
#include "bmlib.h"

int	main(void)
{
	// char	command[] = "awk \'\"\'\"\'{count++} END {print count}\'\"\'\"\'";
	// char	command[] = "awk \"{count++} END {printf \\\"count: %i\\\" , count}\"";
//	char	command[] = "sed    \"s/And/But/\"";
//	char	command[] = "awk \"\'{count++} END {print count}\'\"";
//	char	command[] = "hola 1";
//	char	command[] = "./\"script space.sh\"";
//	char	command[] = "./\"script\\\"quote.sh\"";
//	char	command[] = "./\'\"\'\"\'script space.sh\'\"\'\"\'";
	char	command[] = "awk he he he \"sdfsdf\"\\\"sdfsf";

	ft_printf("\n\t=-=-=-=THE INPUT=-=-=-=-\n<%s>\n\n\t=-=-=-=THE RESULT=-=-=-=-\n", command);

	char	**my_own = ft_cmd_split(command);
	while (*my_own)
		ft_printf("<%s>\n", *(my_own++));
}