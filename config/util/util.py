import os,glob

if(__name__=="__main__"):
    processes=["WPWP"]
    cwd=os.getcwd()
    for process in processes:
        path="/nfs/dust/cms/user/albrechs/production/ntuples/NT_%s"%process
        os.chdir(path)
        with open(cwd+'/test.conf','wt') as fout:
            files=glob.glob("*.root")
            files.sort()
            for file in files:
                file_index=file[file.find('%s_'%process)+(len(process)+1):file.find(".root")]
                print file,'-',file_index
                fout.write('<In FileName="%s/%s" Lumi="0.0"/>\n'%(path,file))
