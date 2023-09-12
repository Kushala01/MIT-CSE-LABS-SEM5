/*WAP to print out the complete stat structure of a file.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

const char * perms(__mode_t mode){
	static char buf[16]={0};
	int i=0;
	buf[i++]=((mode & S_IRUSR) ? 'r':'-');
	buf[i++]=((mode & S_IWUSR) ? 'w':'-');
	buf[i++]=((mode & S_IXUSR) ? 'x':'-');

	buf[i++]=((mode & S_IRGRP) ? 'r':'-');
	buf[i++]=((mode & S_IWGRP) ? 'w':'-');
	buf[i++]=((mode & S_IXGRP) ? 'x':'-');

	buf[i++]=((mode & S_IROTH) ? 'r':'-');
	buf[i++]=((mode & S_IWOTH) ? 'w':'-');
	buf[i++]=((mode & S_IXOTH) ? 'x':'-');

	return buf;
}

int main(int argc, char const* argv[]){
	if(argc <2){
		printf("didnt enter the inp file");
		perror("enter filename");
		return 1;
	}

	struct stat ans;

	int returnVal=stat(argv[1],&ans);

	if(returnVal!=0){
		perror("stat");
		return 1;
	}

	printf("\ninode %ld \n filename %s\n",ans.st_ino,argv[1]);
	printf("device control id: %ld\n",ans.st_dev);
	printf("mode: %10.10s\n",perms(ans.st_mode));
	printf("hark link: %ld\n",ans.st_nlink);
	printf("u id: %d\n",ans.st_uid);
	printf("g id: %d\n",ans.st_gid);
	printf("Device ID: %ld\n", ans.st_rdev);
	printf("Total Size: %ld\n", ans.st_size);
	printf("Block Size: %ld\n", ans.st_blksize); 
	printf("Number of blocks: %ld\n", ans.st_blocks);
	printf("last access time: %s\n", ctime(&ans.st_atime));
	printf("last modified time: %s\n", ctime(&ans.st_mtime));
	printf("last status: %s\n", ctime(&ans.st_ctime));

	switch (ans.st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("File Type: Regular File\n");
        break;
    case S_IFDIR:
        printf("File Type: Directory\n");
        break;
    case S_IFLNK:
        printf("File Type: Symbolic Link\n");
        break;
    case S_IFCHR:
        printf("File Type: Character Device\n");
        break;
    case S_IFBLK:
        printf("File Type: Block Device\n");
        break;
    case S_IFIFO:
        printf("File Type: FIFO/Named Pipe\n");
        break;
    case S_IFSOCK:
        printf("File Type: Socket\n");
        break;
    default:
        printf("File Type: Unknown\n");
        break;
    }
	return 0;
}
