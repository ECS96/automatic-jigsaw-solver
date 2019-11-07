# automatic-jigsaw-solver

Project is read only. So therefore contains no dependencies to run.

Preprocessing of Jigsaw Image data is handled in ImageOperations.

Abstraction of information and the Quantifying of Jigsaw Piece data is computed in ExtractionMethods.

Puzzle and PieceNode are used to pair Pieces and assemble the jigsaw based on Edges matching.

Piece and Edge store the information on each puzzle piece that is extracted from the images.

Matching calculates the likelihood that two pieces are a match based on the displacement between the pieces when
the edges are aligned.

The scores of every comparison are stored in AllScores.txt and the best scores for each pair are stored in BestScores.txt

The types that can be extracted in ExtractionMethods are stored in types.txt
