/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:18:10 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/04 17:22:27 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_prompt(char *line, t_env *envp)
{
	t_parser	*parser;

	parser = init();
	if (line)
		add_history(line);
	parsing_symbols(parser, line, envp);
}
void	set_signal(int sig)
{
	printf("%d",sig);
	if(sig == SIGUSR1)
		signal(SIGQUIT, sig_handler);
	else
		signal(CTRL_C, sig_handler);
		
}

static void	start_minishell(char **env)
{
	char	*line;
	t_env	*envp;

	envp = create_env(env);
	while (1)
	{
		
		//set_signal(SIGUSR1);
		style_prompt();
		line = readline(":> ");
		if (line == NULL)
			ft_exit_with_line(line);
		/*if(line && g_code == 138)
			ft_exit_with_line(line);*/
		if (ft_strlen(line) > 0)
			show_prompt(line, envp);
		free(line);
	}
	free(envp);
}
/*Quand bash fonctionne de manière interactive, il ignore le signal SIGTERM (c'est pourquoi kill 0 ne tue pas un shell interactif), et le signal SIGINT est intercepté et géré (c'est pourquoi la commande interne wait n'est pas interruptible). Dans tous les cas, bash ignore le signal SIGQUIT. Si le contrôle de jobs est disponible, bash ignore les signaux SIGTTIN, SIGTTOU, et SIGTSTP.
Les commandes externes lancées par bash reçoivent les valeurs des signaux héritées par le shell de leur parent. Quand le contrôle de job n'est pas actif, les jobs en arrière-plan ignorent les signaux SIGINT et SIGQUIT en plus des gestionnaires hérités. Les commandes exécutées en tant que résultat de la substitution de commandes ignorent les signaux de contrôle de jobs émis par le clavier SIGTTIN, SIGTTOU, et SIGTSTP.
Par défaut, le shell se termine à la réception de SIGHUP. Avant de se terminer, un shell interactif renvoie SIGHUP à tous les jobs en cours ou arrêtés. Les jobs arrêtés reçoivent aussi SIGCONT pour s'assurer qu'il recevront bien le SIGHUP. Pour empêcher le shell d'envoyer ce signal à un job particulier, il faut le retirer de la table des jobs à l'aide de la commande interne disown (voir FONCTIONS INTERNES DU SHELL plus bas) ou le marquer comme exempté de SIGHUP avec disown -h.
Si l'option du shell huponexit a été activée avec la fonction shopt, bash envoie un signal SIGHUP à tous les jobs lorsqu'un shell de login interactif se termine.
Lorsque bash attend la fin d'une commande et qu'il reçoit un signal qu'il doit capturer, le gestionnaire de signal ne sera pas exécuté avant que la commande soit finie. Lorsque bash attend la fin d'une commande asynchrone avec wait la réception d'un signal capturé causera la fin immédiate de la commande wait avec un code de retour supérieur à 128, à la suite de quoi le gestionnaire de signal sera exécuté.*/
void	sig_handler(int signo)
{
	
	
	if (signo == SIGINT)
	{
		g_code = 1;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		
	}
	
	else if (signo == SIGQUIT)
	{
		g_code = 138;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	start_minishell(env);
	return (0);
}
