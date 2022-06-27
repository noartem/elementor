run-example-gallery:
	xmake f -m release && xmake build && xmake run example-gallery

run-example-gallery-debug:
	xmake f -m debug && xmake build && xmake run example-gallery

run-example-diary:
	cp src/examples/diary/diary.csv build/linux/x86_64/release/diary.csv
	xmake f -m release && xmake build && xmake run example-diary

run-example-diary-debug:
	cp src/examples/diary/diary.csv build/linux/x86_64/debug/diary.csv
	xmake f -m debug && xmake build && xmake run example-diary