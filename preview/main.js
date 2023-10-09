window.onload = function () {
    let solCanvas = document.querySelector("#solCanvas");
    let sctx = solCanvas.getContext("2d");

    // initialize array with all values set to zero
    const maze = Array.from({ length: W * H }, value => 0);

    backTrack(maze);

    document.getElementById("mazeData").innerHTML = JSON.stringify({w: W, h: H, maze: maze, sol: []});

    drawMaze(maze);
}