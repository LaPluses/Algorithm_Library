int mex(vector < int > & vi){
	if(vi.empty()) return 0;
	sort(vi.begin(),vi.end());
	if(vi[0]!=0) return 0;
	for(int i = 1 ; i < vi.size() ; ++ i){
		if(vi[i]-vi[i-1]>1)
			return vi[i-1] + 1;
	}
	return vi.back()+1;
}