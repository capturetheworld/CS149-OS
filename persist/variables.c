return moffset_t
argument int fd
argument char str[] //?? string of characters


create char* ptr = (casted char *) fhdr 

if(search(str )){ //look for the string of characters

	return 0 and print and error
}


//TURN THIS INTO A FUNCTION CREATE ENTRY??

struct entry_s entryToAdd 
//create struct
    entryToAdd.magic = 0xda7a //mem.h short
    entryToAdd.length = length of string + 1 //null??


struct entry_s* entryToAdd_p //pointer to entry allocate

= entrytoAdd's size + length of characters '


//memcpy(dest, source, size)
memcpy(entrytoaddpointer, addressof entry to add, size of entry to add)
memcpy(size of entry+entryToAddpointer, string, entrytoadd length which is length of string +1)

//IS THIS ^^ WHERE THE STRING IS ADDED TO ENTRY????

create moffset_t offset = size of pointer to fileheader fhdr





if(!fhdr-> data_start type moffset_t) //huh this was never intilized? how does this work
{
	set data_start to free_start //not sure
	memcpy (ptr to fhdr + offset, from entryToAdd pointer, size of entry to add and entry to add length)

set fileheader freestart to the length above  size of entry to add and entry to add length

///what is this I'm confused???

return offset!!!

}







