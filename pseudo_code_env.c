#include "include/struct.h"

int		env_init(t_env_info *env_info, char **envp);
int		env_terminate(t_env **env);

t_env	*envnew(char *s);
void	env_del(t_env *env, char *key);

void	envadd_back(t_env **env, t_env *new);

void	envprint(t_env *env);

char	**make_envp(t_env *env, int env_size);

t_env	*find_env(t_env *env, char *key); 
int		is_valid_env_first_name(char c);
int		is_valid_env_name(char c);
char	*set_env_key(char *s);
char	*getenv(const char *key); // 허용함수

void	export_new(t_env_info *env_info, char *envp);

main char **envp 초기화
	*envp = ""
	while (*envp)
	{
		새 노드
	}
	
	- env_init()
		- envnew()
			-  set_env_key()
		- envadd_back()
	- char **envp
expansion
	- set_env_key()
	- getenv() // 허용함수
builtin_export
	- export aa=fed
		- 갱신
			- env = find_env()
			- change_value(t_env *env, char *s)
				- char *value
				- env->value = value;
		- 추가
			- envnew()
			- envadd_back()
	- export
builtin_unset
	- unset aa
		- env_del() -> 중간에 지워지면 이어야되
builtin_cd
	- PWD
	- OLD_PWD
execute
	- $_
	- cmd_to_path() ($PATH)
		- getenv()


