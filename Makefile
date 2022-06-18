run:
	xmake f -m release && xmake build && xmake run examples

run-debug:
	xmake f -m debug && xmake build && xmake run examples