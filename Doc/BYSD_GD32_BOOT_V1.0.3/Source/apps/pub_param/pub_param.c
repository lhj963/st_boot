



typedef struct tagPubParam
{
	unsigned char mdm_dbg_flag : 1;

}PubParam;


PubParam s_stPubParam = {0};


unsigned char is_mdm_dbg_mode(void)
{
	return s_stPubParam.mdm_dbg_flag;
}

void set_mdm_dbg_mode(unsigned char val)
{
	s_stPubParam.mdm_dbg_flag = val;
}







