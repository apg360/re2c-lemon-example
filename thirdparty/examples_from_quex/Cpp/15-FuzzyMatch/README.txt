Samples Applications for Edit-Distance Functions
------------------------------------------------------------------------------

Edit distance functions produce patterns which are similar to a nominal
pattern. Operations such as 'insert', 'delete', 'substitute', and 'transpose'
model the deviations. Sample applications are:

(*) dna_statistics:

   (dna.c, dna.qx) 

   Identifies DNA motifs in a DNA sequences applying while being tolerant with
   respect to a given Levenshtein distance. A mini-self-made DNA string is given
   in 

         dna-sample.txt

   The result is a list of found patterns together with their position of 
   occurrence. Finally, a statistic on occurrences is printed.

(*) vowel_tolerance:

   (vowel-tolerance.c, vowel-tolerance.qx)

   In this example, it is shown how to analyze text in arabic with an
   arbitrarily precise vowel-ization. For that, the '\EdDelete' operation is
   applied on the set of vowels as they are defined in Unicode. Example input
   files:

         vowel-arabic.txt 
         vowel-less-arabic.txt

   Both trigger the same tokens, since the lexer is tolerant with respect to
   vowels being present or not.

(*) spelling:

    (spelling.c, spelling.qx)

    Applies PseudoDamerau distances to match orthographically miss-spelled 
    words. Example file: 

         spelling.txt

------------------------------------------------------------------------------

