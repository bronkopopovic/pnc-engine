from bs4 import BeautifulSoup
infile = open("studio_room.xml","r")
contents = infile.read()
soup = BeautifulSoup(contents,'xml')
titles = soup.find_all('title')
for title in titles:
    print(title.get_text())