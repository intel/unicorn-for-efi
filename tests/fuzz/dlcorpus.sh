#/bin/sh
#change to script directory
cd `dirname $0`
rm -rf corpus_*
ls fuzz_emu*.c | sed 's/\.c//' | while read target
do
    #download public corpus
    rm -f public.zip
    wget "https://storage.googleapis.com/unicorn-backup.clusterfuzz-external.appspot.com/corpus/libFuzzer/unicorn_$target/public.zip"
    unzip -q public.zip -d corpus_$target
    #run target on corpus
    ./$target corpus_$target
done
