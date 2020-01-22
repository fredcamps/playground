resource "aws_s3_bucket" "playground-bucket" {
  provider = aws.playground
  bucket   = "playground-bucket-fredcampos"
  acl      = "private"

  tags = {
    Name        = "Hello World"
    Environment = "Dev"
  }
}

resource "aws_s3_bucket_object" "playground-bucket-object" {
  provider               = aws.playground
  key                    = "txtfile.txt"
  bucket                 = aws_s3_bucket.playground-bucket.id
  source                 = "file.txt"
  server_side_encryption = "AES256"
}

output "aws_s3_info" {
  value = "${aws_s3_bucket.playground-bucket.bucket} saving ${aws_s3_bucket_object.playground-bucket-object.key} file"
}
