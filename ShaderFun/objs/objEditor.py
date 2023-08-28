

def remove_third_vt_value(obj_file_path, output_file_path):
    with open(obj_file_path, 'r') as f:
        lines = f.readlines()

    new_lines = []

    for line in lines:
        if line.startswith('vt '):
            vt_values = line.strip().split()[1:]
            new_vt_line = 'vt ' + ' '.join(vt_values[:2]) + '\n'
            new_lines.append(new_vt_line)
        else:
            new_lines.append(line)

    with open(output_file_path, 'w') as f:
        f.writelines(new_lines)

if __name__ == "__main__":
    input_obj_file = "cat.obj"  # Replace with your input OBJ file path
    output_obj_file = "cat_PROCESSED.obj"  # Replace with desired output OBJ file path

    remove_third_vt_value(input_obj_file, output_obj_file)
    print("Texture coordinate modification complete.")