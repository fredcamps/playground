provider "aws" {
  version = "~> 2.32"
  alias = "playground"
  region = var.awsConfs.region
  shared_credentials_file = "./.credentials"
  profile = var.awsConfs.profile
}
