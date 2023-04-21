#include "bmp.h"


int LoadImage (FILE *file, BmpImage *img)
{
    if (file == nullptr || img == nullptr) return BMP_NULLPTR;

    fseek (file, 0, SEEK_SET);

    read_bmp_file_header (file, &(img -> bmpfh));
    read_bmp_info_header (file, &(img -> bmpih));
    
    if (img -> bmpih.bit_count != 32)
    {
        printf ("Sorry, only 32 bits format is currently supported :(\n");
        return BMP_WRONG_FORMAT;
    }

    img -> pixels = (RGBA *) calloc (img -> bmpih.image_size, sizeof (img -> pixels [0]));
    
    fseek (file, img -> bmpfh.off_bits, SEEK_SET);
    fread (img -> pixels, sizeof (img -> pixels [0]), img -> bmpih.image_size, file);

    img -> width  = img -> bmpih.width;
    img -> height = img -> bmpih.height;

    return BMP_OK;
}

void ImgDtor (BmpImage *img)
{
    if (img == nullptr) return;

    free (img -> pixels);
}

int SaveImage (FILE *file, BmpImage *img)
{
    if (file == nullptr || img == nullptr) return BMP_NULLPTR;

    fseek (file, 0, SEEK_SET);

    write_bmp_file_header (file, &(img -> bmpfh));
    write_bmp_info_header (file, &(img -> bmpih));
    
    fseek (file, img -> bmpfh.off_bits, SEEK_SET);
    fwrite (img -> pixels, sizeof (img -> pixels [0]), img -> bmpih.image_size, file);

    return BMP_OK;
}

void read_bmp_file_header (FILE *file, BMP_FILE_HEADER *bmpfh)
{
    fread (&(bmpfh -> type     ), 1, sizeof (bmpfh -> type     ), file);
    fread (&(bmpfh -> size     ), 1, sizeof (bmpfh -> size     ), file);
    fread (&(bmpfh -> reserved1), 1, sizeof (bmpfh -> reserved1), file);
    fread (&(bmpfh -> reserved2), 1, sizeof (bmpfh -> reserved2), file);
    fread (&(bmpfh -> off_bits ), 1, sizeof (bmpfh -> off_bits ), file);
}

void read_bmp_info_header (FILE *file, BMP_INFO_HEADER *bmpih)
{
    fread (&(bmpih -> size          ), 1, sizeof (bmpih -> size          ), file);
    fread (&(bmpih -> width         ), 1, sizeof (bmpih -> width         ), file);
    fread (&(bmpih -> height        ), 1, sizeof (bmpih -> height        ), file);
    fread (&(bmpih -> planes        ), 1, sizeof (bmpih -> planes        ), file);
    fread (&(bmpih -> bit_count     ), 1, sizeof (bmpih -> bit_count     ), file);
    fread (&(bmpih -> compression   ), 1, sizeof (bmpih -> compression   ), file);
    fread (&(bmpih -> image_size    ), 1, sizeof (bmpih -> image_size    ), file);
    fread (&(bmpih -> x_px_per_meter), 1, sizeof (bmpih -> x_px_per_meter), file);
    fread (&(bmpih -> y_px_per_meter), 1, sizeof (bmpih -> y_px_per_meter), file);
    fread (&(bmpih -> clr_important ), 1, sizeof (bmpih -> clr_important ), file);
    fread (&(bmpih -> clr_used      ), 1, sizeof (bmpih -> clr_used      ), file);
}

void write_bmp_file_header (FILE *file, BMP_FILE_HEADER *bmpfh)
{
    fwrite (&(bmpfh -> type     ), 1, sizeof (bmpfh -> type     ), file);
    fwrite (&(bmpfh -> size     ), 1, sizeof (bmpfh -> size     ), file);
    fwrite (&(bmpfh -> reserved1), 1, sizeof (bmpfh -> reserved1), file);
    fwrite (&(bmpfh -> reserved2), 1, sizeof (bmpfh -> reserved2), file);
    fwrite (&(bmpfh -> off_bits ), 1, sizeof (bmpfh -> off_bits ), file);
}

void write_bmp_info_header (FILE *file, BMP_INFO_HEADER *bmpih)
{
    fwrite (&(bmpih -> size          ), 1, sizeof (bmpih -> size          ), file);
    fwrite (&(bmpih -> width         ), 1, sizeof (bmpih -> width         ), file);
    fwrite (&(bmpih -> height        ), 1, sizeof (bmpih -> height        ), file);
    fwrite (&(bmpih -> planes        ), 1, sizeof (bmpih -> planes        ), file);
    fwrite (&(bmpih -> bit_count     ), 1, sizeof (bmpih -> bit_count     ), file);
    fwrite (&(bmpih -> compression   ), 1, sizeof (bmpih -> compression   ), file);
    fwrite (&(bmpih -> image_size    ), 1, sizeof (bmpih -> image_size    ), file);
    fwrite (&(bmpih -> x_px_per_meter), 1, sizeof (bmpih -> x_px_per_meter), file);
    fwrite (&(bmpih -> y_px_per_meter), 1, sizeof (bmpih -> y_px_per_meter), file);
    fwrite (&(bmpih -> clr_important ), 1, sizeof (bmpih -> clr_important ), file);
    fwrite (&(bmpih -> clr_used      ), 1, sizeof (bmpih -> clr_used      ), file);
}