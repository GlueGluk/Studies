package DeepClone;
# vim: noet:

use 5.016;
use warnings;

=encoding UTF8

=head1 SYNOPSIS

Клонирование сложных структур данных

=head1 clone($orig)

Функция принимает на вход ссылку на какую либо структуру данных и отдаюет, в качестве результата, ее точную независимую копию.
Это значит, что ни один элемент результирующей структуры, не может ссылаться на элементы исходной, но при этом она должна в точности повторять ее схему.

Входные данные:
* undef
* строка
* число
* ссылка на массив
* ссылка на хеш
Элементами ссылок на массив и хеш, могут быть любые из указанных выше конструкций.
Любые отличные от указанных типы данных -- недопустимы. В этом случае результатом клонирования должен быть undef.

Выходные данные:
* undef
* строка
* число
* ссылка на массив
* ссылка на хеш
Элементами ссылок на массив или хеш, не могут быть ссылки на массивы и хеши исходной структуры данных.

=cut

sub clone {
	my %seen;
	my $bad;
	my $clone1;
	$clone1 = sub {
		my $orig = shift;
		if ((defined $orig) && (exists $seen{$orig})) {
			return $seen{$orig};
		}
		my $tCheck = ref $orig;
		if ($tCheck eq 'ARRAY'){
			my @arr = @$orig;
			$seen{$orig} = \@arr;
			for my $el (@arr) {
				$el = $clone1 -> ($el);
				if ($bad){
					last;
				}
			}
			return \@arr;
		}		
		elsif ($tCheck eq 'HASH'){
			my %hash = %$orig;
			$seen{$orig} = \%hash;
			for my $el (keys %hash) {
				$hash{$el} = $clone1 -> ($hash{$el});
                if ($bad){
					last;
				}
			}
			return \%hash;
		}		
		elsif ($tCheck eq "") {
			return $orig;
		}
		else {
			$bad = 1;
		}
	};
	my $res = $clone1 -> (shift);
	return ($bad) ? undef : $res;
}

1;
