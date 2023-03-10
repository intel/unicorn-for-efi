#/bin/sh
#
# Change to script directory using a subshell (like pushd/popd,
# but for regular sh).
#
(
    cd `dirname $0`

    while test $# -gt 0
    do
        case "$1" in
            --clean) echo "Cleaning any existing corpus data"
                     rm -rf corpus_*
                     ;;
        esac
        shift
    done

    ls fuzz_emu*.c | sed 's/\.c//' | while read target
    do
        if [ ! -d corpus_$target ]; then
            #
            # Download public corups
            #
            rm -f public.zip
            echo Fetching corpus_$target data...
            wget "https://storage.googleapis.com/unicorn-backup.clusterfuzz-external.appspot.com/corpus/libFuzzer/unicorn_$target/public.zip" >/dev/null 2>&1
            unzip -q public.zip -d corpus_$target
        fi

        ./$target corpus_$target
    done
)
