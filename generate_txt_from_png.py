from PIL import Image

pieces = ["bishop_black", "bishop_white", "king_black", "king_white", "night_black",
          "night_white", "pawn_white", "pawn_black", "queen_black", "queen_white",
          "rook_black", "rook_white"]

# for piece in pieces:

# with Image.open("pieces/" + piece + ".png") as im:
with Image.open("pieces/bishop_black.png") as im:
    px = im.load()

with open("bishop_black.txt","w") as file:
    for i in range(45):
        for j in range(45):
            pixel = px[j, i]
            if pixel == (0,0,0,0):
                file.write("b")
            else:
                file.write("w")
            print(pixel)
        file.write("\n")
