문제점!
1. 환경변수 expand 시
	value 에 "" 또는 ''가 오는 경우 지워짐
2. 

env
	$<env_name>
		env_name 은 _, a-z, A-Z 로 앞글자 시작 가능
		env_name 에는 _, a-z, A-Z, 0-9 로 이루어질 수 있음
	char **envp에서  *envp 는 <key>=<value> 로 이루어짐
		USER=chaejkim	key="USER", value="chaejkim"
		$abc+sdf 를 확장할 때,  key="abc"

readcmdline()

parser()
	is_valid_quote() -> err
	tokenizer() -> return(1)
	lexcial_analyze() -> return(1)
	tokens_to_cmds()
		'|' 기준으로 script로 나눔
	check_expansion()
		'\'' 안에 있지 않은, $를 확장
		$ 가 확장인지 아닌지, One-Hot Encoding 처럼 표시
			[1, 0, 0] 인 경우 첫번째 $만 확장이라는 표시
	remove_quote()
		먼저 발견한 '\'' (또는 '"') 를 체크하고, 그 다음에 오는 '\'' (또는 '"') 와 같이 삭제
	expansion()
		$ 가 확장인 경우 value를 찾아옴
		'"' 안에 있지 않은 $의 경우 word_splitting()
	

heredoc_readline()

execute()


	
