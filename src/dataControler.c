
int dc_loadArray(int elementSize, void* p, char* fpath) {
	FILE* fp = fopen(fpath, "rb");
	int len;
	fread(&len, sizeof(int), 1, fp);
	fread(p, elementSize, len, fp);
	fclose(fp);
	return len;
}

void dc_saveArray(int elementSize, void* p, int plen, char* fpath) {
	FILE* fp = fopen(fpath, "wb");
	int s = plen;
	fwrite(&s, sizeof(int), 1, fp);
	fwrite(p, elementSize, plen, fp);
	fclose(fp);
}

// TODO 导入初始数据
void dc_importRawData(char* dirPath){

};