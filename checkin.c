/*---------------------------------------------------------*/
/*这个文件为mouse.c的附属文件，处理所有对鼠标感应的处理	   */
/*---------------------------------------------------------*/ 


int check_up(int x,int y){
    if(x<=btn_pgu_rd_x && x>=btn_pgu_lt_x && y<=btn_pgu_rd_y && y>=btn_pgu_lt_y) return 1; else return 0;
}

int check_down(int x,int y){
    if(x<=btn_pgd_rd_x && x>=btn_pgd_lt_x && y<=btn_pgd_rd_y && y>=btn_pgd_lt_y) return 1; else return 0;
}

int check_add(int x,int y){
    if(x<=btn_add_rd_x && x>=btn_add_lt_x && y<=btn_add_rd_y && y>=btn_add_lt_y) return 1; else return 0;
}

int check_del(int x,int y){
    if(x<=btn_del_rd_x && x>=btn_del_lt_x && y<=btn_del_rd_y && y>=btn_del_lt_y) return 1; else return 0;
}

int check_exp(int x,int y){
    if(x<=btn_exp_rd_x && x>=btn_exp_lt_x && y<=btn_exp_rd_y && y>=btn_exp_lt_y) return 1; else return 0;
}

int check_imp(int x,int y){
    if(x<=btn_imp_rd_x && x>=btn_imp_lt_x && y<=btn_imp_rd_y && y>=btn_imp_lt_y) return 1; else return 0;
}

int check_fnd(int x,int y){
    if(x<=btn_fnd_rd_x && x>=btn_fnd_lt_x && y<=btn_fnd_rd_y && y>=btn_fnd_lt_y) return 1; else return 0;
}

int check_vol(int x,int y){
    if(x<=btn_vol_rd_x && x>=btn_vol_lt_x && y<=btn_vol_rd_y && y>=btn_vol_lt_y) return 1; else return 0;
}

int check_c1(int x,int y){
    if(x<=c1_rd_x && x>=c1_lt_x && y<=c1_rd_y && y>=c1_lt_y) return 1; else return 0;
}

int check_c2(int x,int y){
    if(x<=c2_rd_x && x>=c2_lt_x && y<=c2_rd_y && y>=c2_lt_y) return 1; else return 0;
}

int check_c3(int x,int y){
    if(x<=c3_rd_x && x>=c3_lt_x && y<=c3_rd_y && y>=c3_lt_y) return 1; else return 0;
}

int check_c4(int x,int y){
    if(x<=c4_rd_x && x>=c4_lt_x && y<=c4_rd_y && y>=c4_lt_y) return 1; else return 0;
}


int check_sr1(int x,int y){
    if(x<=btn_sr1_rd_x && x>=btn_sr1_lt_x && y<=btn_sr1_rd_y && y>=btn_sr1_lt_y) return 1; else return 0;
}

int check_sr2(int x,int y){
    if(x<=btn_sr2_rd_x && x>=btn_sr2_lt_x && y<=btn_sr2_rd_y && y>=btn_sr2_lt_y) return 1; else return 0;
}

int check_sr3(int x,int y){
    if(x<=btn_sr3_rd_x && x>=btn_sr3_lt_x && y<=btn_sr3_rd_y && y>=btn_sr3_lt_y) return 1; else return 0;
}

int check_cl1(int x,int y){
    if(x<=btn_cl1_rd_x && x>=btn_cl1_lt_x && y<=btn_cl1_rd_y && y>=btn_cl1_lt_y) return 1; else return 0;
}

int check_cl2(int x,int y){
    if(x<=btn_cl2_rd_x && x>=btn_cl2_lt_x && y<=btn_cl2_rd_y && y>=btn_cl2_lt_y) return 1; else return 0;
}

int check_cl3(int x,int y){
    if(x<=btn_cl3_rd_x && x>=btn_cl3_lt_x && y<=btn_cl3_rd_y && y>=btn_cl3_lt_y) return 1; else return 0;
}

int check_bfnd(int x,int y){
    if(x<=btn_bfnd_rd_x && x>=btn_bfnd_lt_x && y<=btn_bfnd_rd_y && y>=btn_bfnd_lt_y) return 1; else return 0;
}

int check_nonfnd(int x,int y){
    if(x<=btn_nonfnd_rd_x && x>=btn_nonfnd_lt_x && y<=btn_bfnd_rd_y && y>=btn_nonfnd_lt_y) return 1; else return 0;
}

int check_badd(int x,int y){
    if(x<=btn_badd_rd_x && x>=btn_badd_lt_x && y<=btn_badd_rd_y && y>=btn_badd_lt_y) return 1; else return 0;
}

int check_nonadd(int x,int y){
    if(x<=btn_nonadd_rd_x && x>=btn_nonadd_lt_x && y<=btn_badd_rd_y && y>=btn_nonadd_lt_y) return 1; else return 0;
}

int check_insert_name(int x,int y){
    if(x<=insert_name_rd_x && x>=insert_name_lt_x && y<=insert_name_rd_y && y>=insert_name_lt_y) return 1; else return 0;
}

int check_insert_birthday(int x,int y){
    if(x<=insert_birthday_rd_x && x>=insert_birthday_lt_x && y<=insert_birthday_rd_y && y>=insert_birthday_lt_y) return 1; else return 0;
}


int check_insert_gender(int x,int y){
    if(x<=insert_gender_rd_x && x>=insert_gender_lt_x && y<=insert_gender_rd_y && y>=insert_gender_lt_y) return 1; else return 0;
}


int check_insert_telephone(int x,int y){
    if(x<=insert_telephone_rd_x && x>=insert_telephone_lt_x && y<=insert_telephone_rd_y && y>=insert_telephone_lt_y) return 1; else return 0;
}


int check_insert_mail(int x,int y){
    if(x<=insert_mail_rd_x && x>=insert_mail_lt_x && y<=insert_mail_rd_y && y>=insert_mail_lt_y) return 1; else return 0;
}

int check_notfound(int x,int y){
	if(x<=notfound_rd_x && x>=notfound_lt_x && y<=notfound_rd_y && y>=notfound_lt_y) return 1; else return 0;
}

int check_insert_export(int x,int y){
    if(x<=insert_export_rd_x && x>=insert_export_lt_x && y<=insert_export_rd_y && y>=insert_export_lt_y) return 1; else return 0;
}

