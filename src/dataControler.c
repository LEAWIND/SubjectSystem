
void dc_saveArray(int elementSize, void* p, int plen, char* fpath) {
	FILE* fp = fopen(fpath, "wb");
	int s = plen;
	fwrite(&s, sizeof(int), 1, fp);
	fwrite(p, elementSize, plen, fp);
	fclose(fp);
}

int dc_loadArray(int elementSize, void* p, char* fpath) {
	FILE* fp = fopen(fpath, "rb");
	int len;
	fread(&len, sizeof(int), 1, fp);
	fread(p, elementSize, len, fp);
	fclose(fp);
	return len;
}