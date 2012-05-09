convert box.png -crop 2048x2048+0+0 -gaussian-blur 4x4 materials/box_lf.png
convert box.png -crop 2048x2048+2048+0 -gaussian-blur 4x4 materials/box_bk.png
convert box.png -crop 2048x2048+4096+0 -gaussian-blur 4x4 materials/box_rt.png
convert box.png -crop 2048x2048+0+2048 -gaussian-blur 4x4 materials/box_dn.png
convert box.png -crop 2048x2048+2048+2048 -gaussian-blur 4x4 materials/box_up.png
convert box.png -crop 2048x2048+4096+2048 -gaussian-blur 4x4 materials/box_fr.png

