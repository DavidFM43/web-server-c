#!/bin/bash
function Files() {
	make
	./Archivos
	echo ""
	echo "Next Program"
	echo ""
	./Pipes_fork
}
Files
