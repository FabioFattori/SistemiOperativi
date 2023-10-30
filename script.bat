cd bin/;
rm ensomma.txt;
touch ensomma.txt;
echo "PORCOGUIDA!" >> ensomma.txt;
echo "file content before changes:";
cat ensomma.txt;
sed -i 's/GUIDA/budda/' ensomma.txt;

echo "file content after changes:";
cat ensomma.txt;
