
	/*
	// set position
	Place(0, 4);
	// set color
	Get_color(8);
	// print the edges
	for (int i = 0; i <= mapRows; ++i){
		if (i != 0){
			for (int r = 1; r <= 2; ++r){
				printf("\n|");
				for (int j = 1; j <= mapCols; ++j){
					printf("   |");
				}
			}
			printf("\n");
		}
		for (int j = 1; j <= mapCols; ++j){
			printf("+---");
		}
		printf("+");
	}
	// reset color
	output_color;
	// choose
	if (humanChooseX){
		// set color
		Get_color(currentColor);
		// print the edges
		Place(humanChooseY * 4 - 4, humanChooseX * 3 + 1);printf("+---+");
		Place(humanChooseY * 4 - 4, humanChooseX * 3 + 2);printf("|   |");
		Place(humanChooseY * 4 - 4, humanChooseX * 3 + 3);printf("|   |");
		Place(humanChooseY * 4 - 4, humanChooseX * 3 + 4);printf("+---+");
		// reset color
		output_color;
	}
	// print the block
	for (int i = 1; i <= mapRows; ++i){
		for (int j = 1; j <= mapCols; ++j){
			block currentBlock = Ask(i, j);
			if (!CheckVisible(currentBlock)){
				continue;
			}
			Place(j * 4 - 3, i * 3 + 2);
			ShowBlockTop(currentBlock);
			Place(j * 4 - 3, i * 3 + 3);
			ShowBlockBottom(currentBlock);
		}
	}
	// reset color
	output_color;
//	*/
