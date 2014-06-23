#### general
####

AC_DEFUN(AC_SS_MESSAGE,
[
	echo $1
])

AC_DEFUN(AC_SS_FIND_FILE_PATH,
	[
		$3="FAILED"
		for a_dir in $2; do
			for a_file in $1; do
				if test -r "$a_dir/$a_file"; then
					$3=$a_dir
					break 2
				fi
			done
		done	
	]
)

AC_DEFUN(AC_SS_FIND_FILE_PATH_EXT,
	[
		$4="FAILED"

		for a_dir in $2; do
			for a_semidir in $3; do
				for a_file in $1; do
					if test -r "$a_dir/$a_semidir/$a_file"; then
						$4="$a_dir/$a_semidir"
						break 3
					fi
				done
			done
		done
	]
)

