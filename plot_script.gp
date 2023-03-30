#---------------------------------------------------------------------------
# This is a basic gnuplot script to generate a performance comparison
# graph. This example requires an "output.dat" file, which is
# generated by running:
#
#     ./hw8_perf > output.dat
#
# To run this script type the following at the command line
#
#     gnuplot -c plot_script.gp
#
# For example, given output.dat, run the following from the command
# line:
#
#     gnuplot -c plot_script.gp
#---------------------------------------------------------------------------

infile = "output.dat"
outfile1 = "insert_graph.png"
outfile2 = "erase_graph.png"
outfile3 = "sorted_keys_graph.png"

# color scheme
RED = "#e6194B"
GREEN = "#3cb44b"
YELLOW = "#ffe119"
BLUE = "#4363d8"
ORANGE = "#f58231"
PURPLE = "#911eb4"
CYAN = "#42d4f4"
MAGENTA = "#f032e6"
LIME = "#bfef45"
PINK = "#fabed4"
TEAL = "#469990"
LAVENDER = "#dcbeff"
BROWN = "#9A6324"
BEIGE = "#fffac8"
MAROON = "#800000"
MINT = "#aaffc3"
OLIVE = "#808000"
APRICOT = "#ffd8b1"
NAVY = "#000075"
GREY = "#a9a9a9"

# Set the terminal for PNG output and aspect ratio
set terminal pngcairo enhanced font 'Verdana, 10'
set size ratio 0.75

# Set the title and each axis label
set xlabel "Input Size (n)"
set ylabel "Time (msec)"

# Move the key to the left of the graph
set key left

# Turn on the grid
set grid

# Change x-axis to print large numbers
set auto x
set xtics rotate
set xtics 0,15000,150000

# Change y-axis to zero or higher
set yrange [0:*] noreverse writeback

# Save the graph
set output outfile1

# Plot the data
set title "BinSearchMap vs HashMap vs BSTMap vs AVLMap Insert Performance";
plot  infile u 1:2 t "BSTMap Insert" w linespoints lw 3 lc rgb YELLOW pointtype 6, \
      infile u 1:3 t "AVLMap Insert" w linespoints lw 3 lc rgb BLUE pointtype 6, \
      infile u 1:4 t "MinHeap Insert" w linespoints lw 3 lc rgb RED pointtype 6;

# Save the graph
set output outfile2

# Plot the data
set title "BinSearchMap vs HashMap vs BSTMap vs AVLMap Erase Performance";
plot  infile u 1:5 t "BSTMap Erase" w linespoints lw 3 lc rgb YELLOW pointtype 6, \
      infile u 1:6 t "AVLMap Erase" w linespoints lw 3 lc rgb BLUE pointtype 6, \
      infile u 1:7 t "MinHeap Erase" w linespoints lw 3 lc rgb GREEN pointtype 6;


# Save the graph
set output outfile3

# Plot the data
set title "BinSearchMap vs HashMap vs BSTMap vs AVLMap Sorted Keys Performance";
plot  infile u 1:8 t "BSTMap Sorted Keys" w linespoints lw 3 lc rgb YELLOW pointtype 6, \
      infile u 1:9 t "AVLMap Sorted Keys" w linespoints lw 3 lc rgb BLUE pointtype 6, \
      infile u 1:10 t "MinHeap Sorted Keys" w linespoints lw 3 lc rgb GREEN pointtype 6;




