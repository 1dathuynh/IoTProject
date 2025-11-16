import { AppSidebar } from "@/components/app-sidebar";
import {
  Breadcrumb,
  BreadcrumbItem,
  BreadcrumbLink,
  BreadcrumbList,
  BreadcrumbPage,
  BreadcrumbSeparator,
} from "@/components/ui/breadcrumb";
import { Separator } from "@/components/ui/separator";
import {
  SidebarInset,
  SidebarProvider,
  SidebarTrigger,
} from "@/components/ui/sidebar";

export default function Page() {
  return (
    <SidebarProvider>
      <AppSidebar />
      <SidebarInset>
        <header className="flex h-16 items-center gap-4 px-4 border-b border-gray-200 bg-white shadow-sm">
          <div className="flex items-center gap-2">
            <SidebarTrigger className="text-gray-900 hover:text-gray-600" />
            <Separator orientation="vertical" className="h-6 border-gray-300" />
            <Breadcrumb className="text-sm text-gray-600">
              <BreadcrumbList>
                <BreadcrumbItem>
                  <BreadcrumbLink className="text-gray-600 hover:text-black">
                    Trang chủ
                  </BreadcrumbLink>
                </BreadcrumbItem>
                <BreadcrumbSeparator />
                <BreadcrumbItem>
                  <BreadcrumbLink className="text-gray-600 hover:text-black">
                    Bãi đỗ xe
                  </BreadcrumbLink>
                </BreadcrumbItem>
              </BreadcrumbList>
            </Breadcrumb>
          </div>
        </header>

        <div className="flex flex-col gap-6 p-6">
          {/* Giới thiệu */}
          <section className="text-center py-6">
            <h1 className="text-3xl font-bold text-gray-900">
              Chào mừng đến với Hệ thống mô phỏng mở cửa thông minh
            </h1>
            <p className="text-lg text-gray-700 mt-4"></p>
          </section>
        </div>
      </SidebarInset>
    </SidebarProvider>
  );
}
