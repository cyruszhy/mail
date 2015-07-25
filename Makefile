
vpath %.c noblock epollcreat qingchu list getwanip zhuandizhi zhuanfa hash heap neicunchi lock daxiaoduan bianjiema getbody 
vpath %.h noblock epollcreat qingchu list getwanip zhuandizhi zhuanfa hash heap neicunchi lock daxiaoduan bianjiema getbody 
mail:mail.o getwanip.o zhuandizhi.o noblock.o epollcreat.o qingchu.o list.o zhuanfa.o hash.o heap.o neicunchi.o shared.o daxiaoduan.o bianjiema.o getbody.o    
	$(CC) $(LDFLAGS) -o mail mail.o getwanip.o zhuandizhi.o noblock.o epollcreat.o qingchu.o list.o zhuanfa.o hash.o heap.o neicunchi.o shared.o daxiaoduan.o bianjiema.o getbody.o -lpthread -lrt 
clean:
	rm -rf mail mail.o getwanip.o zhuandizhi.o hash.o heap.o neicunchi.o daxiaoduan.o bianjiema.o getbody.o 
