const CWIDTH = 800;
const CHEIGHT = 800;


const drawMaze = (maze) => {
    let mazeCanvas = document.querySelector("#mazeCanvas");
    let mctx = mazeCanvas.getContext("2d");

    mazeCanvas.width = CWIDTH;
    mazeCanvas.height = CHEIGHT;

    let BW = CWIDTH / W;
    let BWQ = BW / 4;
    let BWH = BW / 2;
    let BW3Q = BWQ * 3;

    let BH = CHEIGHT / H;
    let BHQ = BH / 4;
    let BHH = BH / 2;
    let BH3Q = BHQ * 3;

    for (let i = 0; i < W; i++) {
        for (let j = 0; j < H; j++) {
            let val = maze[(H - 1 - j) * W + i];

            mctx.fillStyle = "black";
            mctx.fillRect(i * BW, j * BH, BWQ, BHQ);
            mctx.fillRect(i * BW, j * BH + BH3Q, BWQ, BHQ);
            mctx.fillRect(i * BW + BW3Q, j * BH, BWQ, BHQ);
            mctx.fillRect(i * BW + BW3Q, j * BH + BH3Q, BWQ, BHQ);

            mctx.textAlign = "center";
            //mctx.strokeText(`${val}`, i * BW + BWH, j * BH + BWH);

            if ((val & DIR.UP) == 0) {
                mctx.fillStyle = "red";
                mctx.fillRect(i * BW + BWQ, j * BH, BWH, BHQ);
            }

            if ((val & DIR.DOWN) == 0) {
                mctx.fillStyle = "green";
                mctx.fillRect(i * BW + BWQ, j * BH + BH3Q, BWH, BHQ);
            }

            if ((val & DIR.LEFT) == 0) {
                mctx.fillStyle = "orange";
                mctx.fillRect(i * BW, j * BH + BHQ, BWQ, BHH);
            }

            if ((val & DIR.RIGHT) == 0) {
                mctx.fillStyle = "blue";
                mctx.fillRect(i * BW + BW3Q, j * BH + BHQ, BHQ, BHH);
            }
        }
    }
}