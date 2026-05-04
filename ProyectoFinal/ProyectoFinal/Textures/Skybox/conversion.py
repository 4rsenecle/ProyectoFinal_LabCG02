from PIL import Image

timesList = ["Day", "Night"]
positionList = ["top", "bottom", "left", "right", "front", "back"]
for j in range(2):
    for i in range(6):
        img = Image.open(f"{timesList[j]}Time_Skybox_{positionList[i]}.tga")
        img.convert("RGB").save(f"{timesList[j]}Time_Skybox_{positionList[i]}_converted.tga", compression=None)
