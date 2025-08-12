with open('amar.log', 'r', encoding='utf-8') as file:
    # Read all lines into a list
    lines = file.readlines()

    # Filter out lines starting with 'std' (case-sensitive)
    filtered_lines = [line for line in lines if 'sockpp'  in line.strip()]

    # Print or process the filtered lines
# strip() removes trailing newlines

    # Optionally, write the filtered lines back to the file or a new file
with open('amar1.log', 'w', encoding='utf-8') as file:
    file.writelines(filtered_lines)
